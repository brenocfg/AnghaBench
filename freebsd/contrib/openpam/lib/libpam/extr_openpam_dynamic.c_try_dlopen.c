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

/* Variables and functions */
 int /*<<< orphan*/  OPENPAM_VERIFY_MODULE_FILE ; 
 int /*<<< orphan*/  PAM_LOG_ERROR ; 
 int /*<<< orphan*/  PAM_LOG_LIBDEBUG ; 
 int /*<<< orphan*/  RTLD_NOW ; 
 int /*<<< orphan*/  dlerror () ; 
 void* dlopen (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ openpam_check_path_owner_perms (char const*) ; 
 int /*<<< orphan*/  openpam_get_feature (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  openpam_log (int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static void *
try_dlopen(const char *modfn)
{
	int check_module_file;
	void *dlh;

	openpam_log(PAM_LOG_LIBDEBUG, "dlopen(%s)", modfn);
	openpam_get_feature(OPENPAM_VERIFY_MODULE_FILE,
	    &check_module_file);
	if (check_module_file &&
	    openpam_check_path_owner_perms(modfn) != 0)
		return (NULL);
	if ((dlh = dlopen(modfn, RTLD_NOW)) == NULL) {
		openpam_log(PAM_LOG_ERROR, "%s: %s", modfn, dlerror());
		errno = 0;
		return (NULL);
	}
	return (dlh);
}