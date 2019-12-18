#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct casper_service {int /*<<< orphan*/  cs_service; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOTCAPABLE ; 
 int /*<<< orphan*/  casper_allowed_service (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_exists_string (int /*<<< orphan*/ *,char*) ; 
 char* nvlist_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_move_descriptor (int /*<<< orphan*/ *,char*,int) ; 
 int nvlist_send (int,int /*<<< orphan*/ *) ; 
 struct casper_service* service_find (char const*) ; 
 int /*<<< orphan*/  service_get_channel_flags (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int zygote_clone_service_execute (int*,int*) ; 

__attribute__((used)) static int
casper_command(const char *cmd, const nvlist_t *limits, nvlist_t *nvlin,
    nvlist_t *nvlout)
{
	struct casper_service *casserv;
	const char *servname;
	nvlist_t *nvl;
	int chanfd, procfd, error;

	if (strcmp(cmd, "open") != 0)
		return (EINVAL);
	if (!nvlist_exists_string(nvlin, "service"))
		return (EINVAL);

	servname = nvlist_get_string(nvlin, "service");
	casserv = service_find(servname);
	if (casserv == NULL)
		return (ENOENT);

	if (!casper_allowed_service(limits, servname))
		return (ENOTCAPABLE);

	if (zygote_clone_service_execute(&chanfd, &procfd) == -1)
		return (errno);

	nvl = nvlist_create(0);
	nvlist_add_string(nvl, "service", servname);
	nvlist_move_descriptor(nvl, "procfd", procfd);
	if (nvlist_send(chanfd, nvl) == -1) {
		error = errno;
		nvlist_destroy(nvl);
		close(chanfd);
		return (error);
	}
	nvlist_destroy(nvl);

	nvlist_move_descriptor(nvlout, "chanfd", chanfd);
	nvlist_add_number(nvlout, "chanflags",
	    service_get_channel_flags(casserv->cs_service));

	return (0);
}