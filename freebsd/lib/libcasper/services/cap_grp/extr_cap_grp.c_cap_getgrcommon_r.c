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
typedef  int /*<<< orphan*/  uint64_t ;
struct group {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ gid_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * cap_xfer_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 char* gbuffer ; 
 size_t gbufsize ; 
 int group_resize () ; 
 int group_unpack (int /*<<< orphan*/ *,struct group*,char*,size_t) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_exists_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
cap_getgrcommon_r(cap_channel_t *chan, const char *cmd, const char *name,
    gid_t gid, struct group *grp, char *buffer, size_t bufsize,
    struct group **result)
{
	nvlist_t *nvl;
	bool getgr_r;
	int error;

	nvl = nvlist_create(0);
	nvlist_add_string(nvl, "cmd", cmd);
	if (strcmp(cmd, "getgrent") == 0 || strcmp(cmd, "getgrent_r") == 0) {
		/* Add nothing. */
	} else if (strcmp(cmd, "getgrnam") == 0 ||
	    strcmp(cmd, "getgrnam_r") == 0) {
		nvlist_add_string(nvl, "name", name);
	} else if (strcmp(cmd, "getgrgid") == 0 ||
	    strcmp(cmd, "getgrgid_r") == 0) {
		nvlist_add_number(nvl, "gid", (uint64_t)gid);
	} else {
		abort();
	}
	nvl = cap_xfer_nvlist(chan, nvl);
	if (nvl == NULL) {
		assert(errno != 0);
		*result = NULL;
		return (errno);
	}
	error = (int)nvlist_get_number(nvl, "error");
	if (error != 0) {
		nvlist_destroy(nvl);
		*result = NULL;
		return (error);
	}

	if (!nvlist_exists_string(nvl, "gr_name")) {
		/* Not found. */
		nvlist_destroy(nvl);
		*result = NULL;
		return (0);
	}

	getgr_r = (strcmp(cmd, "getgrent_r") == 0 ||
	    strcmp(cmd, "getgrnam_r") == 0 || strcmp(cmd, "getgrgid_r") == 0);

	for (;;) {
		error = group_unpack(nvl, grp, buffer, bufsize);
		if (getgr_r || error != ERANGE)
			break;
		assert(buffer == gbuffer);
		assert(bufsize == gbufsize);
		error = group_resize();
		if (error != 0)
			break;
		/* Update pointers after resize. */
		buffer = gbuffer;
		bufsize = gbufsize;
	}

	nvlist_destroy(nvl);

	if (error == 0)
		*result = grp;
	else
		*result = NULL;

	return (error);
}