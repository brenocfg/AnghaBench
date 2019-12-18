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
typedef  scalar_t__ uid_t ;
struct passwd {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * cap_xfer_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 char* gbuffer ; 
 size_t gbufsize ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_exists_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/ *,char*) ; 
 int passwd_resize () ; 
 int passwd_unpack (int /*<<< orphan*/ *,struct passwd*,char*,size_t) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
cap_getpwcommon_r(cap_channel_t *chan, const char *cmd, const char *login,
    uid_t uid, struct passwd *pwd, char *buffer, size_t bufsize,
    struct passwd **result)
{
	nvlist_t *nvl;
	bool getpw_r;
	int error;

	nvl = nvlist_create(0);
	nvlist_add_string(nvl, "cmd", cmd);
	if (strcmp(cmd, "getpwent") == 0 || strcmp(cmd, "getpwent_r") == 0) {
		/* Add nothing. */
	} else if (strcmp(cmd, "getpwnam") == 0 ||
	    strcmp(cmd, "getpwnam_r") == 0) {
		nvlist_add_string(nvl, "name", login);
	} else if (strcmp(cmd, "getpwuid") == 0 ||
	    strcmp(cmd, "getpwuid_r") == 0) {
		nvlist_add_number(nvl, "uid", (uint64_t)uid);
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

	if (!nvlist_exists_string(nvl, "pw_name")) {
		/* Not found. */
		nvlist_destroy(nvl);
		*result = NULL;
		return (0);
	}

	getpw_r = (strcmp(cmd, "getpwent_r") == 0 ||
	    strcmp(cmd, "getpwnam_r") == 0 || strcmp(cmd, "getpwuid_r") == 0);

	for (;;) {
		error = passwd_unpack(nvl, pwd, buffer, bufsize);
		if (getpw_r || error != ERANGE)
			break;
		assert(buffer == gbuffer);
		assert(bufsize == gbufsize);
		error = passwd_resize();
		if (error != 0)
			break;
		/* Update pointers after resize. */
		buffer = gbuffer;
		bufsize = gbufsize;
	}

	nvlist_destroy(nvl);

	if (error == 0)
		*result = pwd;
	else
		*result = NULL;

	return (error);
}