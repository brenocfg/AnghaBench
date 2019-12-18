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
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_6__ {scalar_t__ fa_magic; int /*<<< orphan*/ * fa_chann; } ;
typedef  TYPE_1__ fileargs_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTCAPABLE ; 
 scalar_t__ FILEARGS_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fileargs_fetch (TYPE_1__*,char const*,char*) ; 
 int fileargs_get_fd_cache (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  fileargs_set_cache (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int nvlist_take_descriptor (int /*<<< orphan*/ *,char*) ; 
 char* nvlist_take_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
fileargs_open(fileargs_t *fa, const char *name)
{
	int fd;
	nvlist_t *nvl;
	char *cmd;

	assert(fa != NULL);
	assert(fa->fa_magic == FILEARGS_MAGIC);

	if (name == NULL) {
		errno = EINVAL;
		return (-1);
	}

	if (fa->fa_chann == NULL) {
		errno = ENOTCAPABLE;
		return (-1);
	}

	fd = fileargs_get_fd_cache(fa, name);
	if (fd != -1)
		return (fd);

	nvl = fileargs_fetch(fa, name, "open");
	if (nvl == NULL)
		return (-1);

	fd = nvlist_take_descriptor(nvl, "fd");
	cmd = nvlist_take_string(nvl, "cmd");
	if (strcmp(cmd, "cache") == 0)
		fileargs_set_cache(fa, nvl);
	else
		nvlist_destroy(nvl);
	free(cmd);

	return (fd);
}