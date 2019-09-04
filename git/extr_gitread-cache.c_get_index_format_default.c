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
 unsigned int INDEX_FORMAT_DEFAULT ; 
 unsigned int INDEX_FORMAT_LB ; 
 unsigned int INDEX_FORMAT_UB ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  git_config_get_int (char*,int*) ; 
 unsigned int strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int get_index_format_default(void)
{
	char *envversion = getenv("GIT_INDEX_VERSION");
	char *endp;
	int value;
	unsigned int version = INDEX_FORMAT_DEFAULT;

	if (!envversion) {
		if (!git_config_get_int("index.version", &value))
			version = value;
		if (version < INDEX_FORMAT_LB || INDEX_FORMAT_UB < version) {
			warning(_("index.version set, but the value is invalid.\n"
				  "Using version %i"), INDEX_FORMAT_DEFAULT);
			return INDEX_FORMAT_DEFAULT;
		}
		return version;
	}

	version = strtoul(envversion, &endp, 10);
	if (*endp ||
	    version < INDEX_FORMAT_LB || INDEX_FORMAT_UB < version) {
		warning(_("GIT_INDEX_VERSION set, but the value is invalid.\n"
			  "Using version %i"), INDEX_FORMAT_DEFAULT);
		version = INDEX_FORMAT_DEFAULT;
	}
	return version;
}