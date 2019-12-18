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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * cap_wrap (int,int) ; 
 int /*<<< orphan*/ * cap_xfer_nvlist (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_nvlist_flags (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/ *,char*) ; 
 int nvlist_take_descriptor (int /*<<< orphan*/ *,char*) ; 
 int nvlist_take_number (int /*<<< orphan*/ *,char*) ; 

cap_channel_t *
cap_service_open(const cap_channel_t *chan, const char *name)
{
	cap_channel_t *newchan;
	nvlist_t *nvl;
	int sock, error;
	int flags;

	sock = -1;

	nvl = nvlist_create(channel_nvlist_flags(chan));
	nvlist_add_string(nvl, "cmd", "open");
	nvlist_add_string(nvl, "service", name);
	nvl = cap_xfer_nvlist(chan, nvl);
	if (nvl == NULL)
		return (NULL);
	error = (int)nvlist_get_number(nvl, "error");
	if (error != 0) {
		nvlist_destroy(nvl);
		errno = error;
		return (NULL);
	}
	sock = nvlist_take_descriptor(nvl, "chanfd");
	flags = nvlist_take_number(nvl, "chanflags");
	assert(sock >= 0);
	nvlist_destroy(nvl);
	nvl = NULL;
	newchan = cap_wrap(sock, flags);
	if (newchan == NULL)
		goto fail;
	return (newchan);
fail:
	error = errno;
	close(sock);
	errno = error;
	return (NULL);
}