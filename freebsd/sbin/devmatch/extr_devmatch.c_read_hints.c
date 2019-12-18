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
typedef  int /*<<< orphan*/  uintmax_t ;
struct stat {size_t st_size; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,char const*,...) ; 
 scalar_t__ errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 void* malloc (size_t) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 size_t read (int,void*,size_t) ; 

__attribute__((used)) static void *
read_hints(const char *fn, size_t *len)
{
	void *h;
	int fd;
	struct stat sb;

	fd = open(fn, O_RDONLY);
	if (fd < 0) {
		if (errno == ENOENT)
			return NULL;
		err(1, "Can't open %s for reading", fn);
	}
	if (fstat(fd, &sb) != 0)
		err(1, "Can't fstat %s\n", fn);
	h = malloc(sb.st_size);
	if (h == NULL)
		err(1, "not enough space to read hints file of %ju bytes", (uintmax_t)sb.st_size);
	if (read(fd, h, sb.st_size) != sb.st_size)
		err(1, "Can't read in %ju bytes from %s", (uintmax_t)sb.st_size, fn);
	close(fd);
	*len = sb.st_size;
	return h;
}