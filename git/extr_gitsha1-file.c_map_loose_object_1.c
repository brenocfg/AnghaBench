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
struct stat {int /*<<< orphan*/  st_size; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 int git_open (char const*) ; 
 int open_loose_object (struct repository*,struct object_id const*,char const**) ; 
 void* xmmap (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned long xsize_t (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *map_loose_object_1(struct repository *r, const char *path,
			     const struct object_id *oid, unsigned long *size)
{
	void *map;
	int fd;

	if (path)
		fd = git_open(path);
	else
		fd = open_loose_object(r, oid, &path);
	map = NULL;
	if (fd >= 0) {
		struct stat st;

		if (!fstat(fd, &st)) {
			*size = xsize_t(st.st_size);
			if (!*size) {
				/* mmap() is forbidden on empty files */
				error(_("object file %s is empty"), path);
				close(fd);
				return NULL;
			}
			map = xmmap(NULL, *size, PROT_READ, MAP_PRIVATE, fd, 0);
		}
		close(fd);
	}
	return map;
}