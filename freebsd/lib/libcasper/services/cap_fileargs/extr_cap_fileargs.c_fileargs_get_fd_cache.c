#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_3__ {scalar_t__ fa_magic; int fa_fdflags; int /*<<< orphan*/ * fa_cache; } ;
typedef  TYPE_1__ fileargs_t ;

/* Variables and functions */
 scalar_t__ FILEARGS_MAGIC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * dnvlist_get_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_exists_descriptor (int /*<<< orphan*/ *,char*) ; 
 int nvlist_take_descriptor (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * nvlist_take_nvlist (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
fileargs_get_fd_cache(fileargs_t *fa, const char *name)
{
	int fd;
	const nvlist_t *nvl;
	nvlist_t *tnvl;

	assert(fa != NULL);
	assert(fa->fa_magic == FILEARGS_MAGIC);
	assert(name != NULL);

	if (fa->fa_cache == NULL)
		return (-1);

	if ((fa->fa_fdflags & O_CREAT) != 0)
		return (-1);

	nvl = dnvlist_get_nvlist(fa->fa_cache, name, NULL);
	if (nvl == NULL)
		return (-1);

	tnvl = nvlist_take_nvlist(fa->fa_cache, name);

	if (!nvlist_exists_descriptor(tnvl, "fd")) {
		nvlist_destroy(tnvl);
		return (-1);
	}

	fd = nvlist_take_descriptor(tnvl, "fd");
	nvlist_destroy(tnvl);

	if ((fa->fa_fdflags & O_CLOEXEC) != O_CLOEXEC) {
		if (fcntl(fd, F_SETFD, fa->fa_fdflags) == -1) {
			close(fd);
			return (-1);
		}
	}

	return (fd);
}