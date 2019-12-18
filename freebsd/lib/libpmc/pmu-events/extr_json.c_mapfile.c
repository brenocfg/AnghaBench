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
struct stat {size_t st_size; } ;

/* Variables and functions */
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int fstat (int,struct stat*) ; 
 char* mmap (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 unsigned int sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static char *mapfile(const char *fn, size_t *size)
{
	unsigned ps = sysconf(_SC_PAGESIZE);
	struct stat st;
	char *map = NULL;
	int err;
	int fd = open(fn, O_RDONLY);

	if (fd < 0 && verbose > 0 && fn) {
		pr_err("Error opening events file '%s': %s\n", fn,
				strerror(errno));
	}

	if (fd < 0)
		return NULL;
	err = fstat(fd, &st);
	if (err < 0)
		goto out;
	*size = st.st_size;
	map = mmap(NULL,
		   (st.st_size + ps - 1) & ~(ps - 1),
		   PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED)
		map = NULL;
out:
	close(fd);
	return map;
}