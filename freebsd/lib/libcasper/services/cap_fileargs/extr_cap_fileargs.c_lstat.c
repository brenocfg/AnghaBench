#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_6__ {scalar_t__ fa_magic; int /*<<< orphan*/ * fa_chann; } ;
typedef  TYPE_1__ fileargs_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTCAPABLE ; 
 scalar_t__ FILEARGS_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fileargs_fetch (TYPE_1__*,char const*,char*) ; 
 int fileargs_get_lstat_cache (TYPE_1__*,char const*,struct stat*) ; 
 int /*<<< orphan*/  fileargs_set_cache (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (struct stat*,void const*,size_t) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 void* nvlist_get_binary (int /*<<< orphan*/ *,char*,size_t*) ; 
 char* nvlist_take_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
fileargs_lstat(fileargs_t *fa, const char *name, struct stat *sb)
{
	nvlist_t *nvl;
	const void *buf;
	size_t size;
	char *cmd;

	assert(fa != NULL);
	assert(fa->fa_magic == FILEARGS_MAGIC);

	if (name == NULL) {
		errno = EINVAL;
		return (-1);
	}

	if (sb == NULL) {
		errno = EFAULT;
		return (-1);
	}

	if (fa->fa_chann == NULL) {
		errno = ENOTCAPABLE;
		return (-1);
	}

	if (fileargs_get_lstat_cache(fa, name, sb) != -1)
		return (0);

	nvl = fileargs_fetch(fa, name, "lstat");
	if (nvl == NULL)
		return (-1);

	buf = nvlist_get_binary(nvl, "stat", &size);
	assert(size == sizeof(*sb));
	memcpy(sb, buf, size);

	cmd = nvlist_take_string(nvl, "cmd");
	if (strcmp(cmd, "cache") == 0)
		fileargs_set_cache(fa, nvl);
	else
		nvlist_destroy(nvl);
	free(cmd);

	return (0);
}