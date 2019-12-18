#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int index_version; } ;
struct repository {TYPE_1__ settings; } ;

/* Variables and functions */
 unsigned int INDEX_FORMAT_DEFAULT ; 
 unsigned int INDEX_FORMAT_LB ; 
 unsigned int INDEX_FORMAT_UB ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  prepare_repo_settings (struct repository*) ; 
 unsigned int strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int get_index_format_default(struct repository *r)
{
	char *envversion = getenv("GIT_INDEX_VERSION");
	char *endp;
	unsigned int version = INDEX_FORMAT_DEFAULT;

	if (!envversion) {
		prepare_repo_settings(r);

		if (r->settings.index_version >= 0)
			version = r->settings.index_version;
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