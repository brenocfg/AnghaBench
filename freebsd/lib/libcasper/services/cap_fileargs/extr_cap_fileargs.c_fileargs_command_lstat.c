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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  sb ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int ENOTCAPABLE ; 
 int /*<<< orphan*/  FA_LSTAT ; 
 int /*<<< orphan*/  allcached ; 
 int errno ; 
 int /*<<< orphan*/  fileargs_add_cache (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  fileargs_allowed (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lastname ; 
 int lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  nvlist_add_binary (int /*<<< orphan*/ *,char*,struct stat*,int) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 char* nvlist_get_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fileargs_command_lstat(const nvlist_t *limits, nvlist_t *nvlin,
    nvlist_t *nvlout)
{
	int error;
	const char *name;
	struct stat sb;

	if (limits == NULL)
		return (ENOTCAPABLE);

	if (!fileargs_allowed(limits, nvlin, FA_LSTAT))
		return (ENOTCAPABLE);

	name = nvlist_get_string(nvlin, "name");

	error = lstat(name, &sb);
	if (error < 0)
		return (errno);

	if (!allcached && (lastname == NULL ||
	    strcmp(name, lastname) == 0)) {
		nvlist_add_string(nvlout, "cmd", "cache");
		fileargs_add_cache(nvlout, limits, name);
	} else {
		nvlist_add_string(nvlout, "cmd", "lstat");
	}
	nvlist_add_binary(nvlout, "stat", &sb, sizeof(sb));
	return (0);
}