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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fwrite (char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,int) ; 
 int shm_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
read_one_shm(const char *path)
{
	char buf[4096];
	ssize_t size, se;
	int fd, ret;

	ret = 1;
	fd = shm_open(path, O_RDONLY, 0);
	if (fd == -1) {
		warn("open %s", path);
		goto out;
	}
	for (;;) {
		size = read(fd, buf, sizeof(buf));
		if (size > 0) {
			se = fwrite(buf, 1, size, stdout);
			if (se < size) {
				warnx("short write to stdout");
				goto out;
			}
		}
		if (size == (ssize_t)sizeof(buf))
			continue;
		if (size >= 0 && size < (ssize_t)sizeof(buf)) {
			ret = 0;
			goto out;
		}
		warn("read from %s", path);
		goto out;
	}
out:
	close(fd);
	return (ret);
}