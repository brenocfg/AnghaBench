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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ mode_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 scalar_t__ MAXPATHLEN ; 
 int /*<<< orphan*/  NV_FLAG_NO_UNIQUE ; 
 int O_CREAT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  nvlist_add_binary (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvlist_add_null (int /*<<< orphan*/ *,char const* const) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const* const) ; 

__attribute__((used)) static nvlist_t *
fileargs_create_limit(int argc, const char * const *argv, int flags,
    mode_t mode, cap_rights_t *rightsp, int operations)
{
	nvlist_t *limits;
	int i;

	limits = nvlist_create(NV_FLAG_NO_UNIQUE);
	if (limits == NULL)
		return (NULL);

	nvlist_add_number(limits, "flags", flags);
	nvlist_add_number(limits, "operations", operations);
	if (rightsp != NULL) {
		nvlist_add_binary(limits, "cap_rights", rightsp,
		    sizeof(*rightsp));
	}
	if ((flags & O_CREAT) != 0)
		nvlist_add_number(limits, "mode", (uint64_t)mode);

	for (i = 0; i < argc; i++) {
		if (strlen(argv[i]) >= MAXPATHLEN) {
			nvlist_destroy(limits);
			errno = ENAMETOOLONG;
			return (NULL);
		}
		nvlist_add_null(limits, argv[i]);
	}

	return (limits);
}