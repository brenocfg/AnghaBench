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

/* Variables and functions */
 int ENOTCAPABLE ; 
 int /*<<< orphan*/  FA_OPEN ; 
 int /*<<< orphan*/  allcached ; 
 int errno ; 
 int /*<<< orphan*/  fileargs_add_cache (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  fileargs_allowed (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lastname ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 char* nvlist_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_move_descriptor (int /*<<< orphan*/ *,char*,int) ; 
 int open_file (char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fileargs_command_open(const nvlist_t *limits, nvlist_t *nvlin,
    nvlist_t *nvlout)
{
	int fd;
	const char *name;

	if (limits == NULL)
		return (ENOTCAPABLE);

	if (!fileargs_allowed(limits, nvlin, FA_OPEN))
		return (ENOTCAPABLE);

	name = nvlist_get_string(nvlin, "name");

	fd = open_file(name);
	if (fd < 0)
		return (errno);

	if (!allcached && (lastname == NULL ||
	    strcmp(name, lastname) == 0)) {
		nvlist_add_string(nvlout, "cmd", "cache");
		fileargs_add_cache(nvlout, limits, name);
	} else {
		nvlist_add_string(nvlout, "cmd", "open");
	}
	nvlist_move_descriptor(nvlout, "fd", fd);
	return (0);
}