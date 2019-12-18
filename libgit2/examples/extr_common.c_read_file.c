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
struct stat {int st_size; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 char* malloc (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 

char *read_file(const char *path)
{
	ssize_t total = 0;
	char *buf = NULL;
	struct stat st;
	int fd = -1;

	if ((fd = open(path, O_RDONLY)) < 0 || fstat(fd, &st) < 0)
		goto out;

	if ((buf = malloc(st.st_size + 1)) == NULL)
		goto out;

	while (total < st.st_size) {
		ssize_t bytes = read(fd, buf + total, st.st_size - total);
		if (bytes <= 0) {
			if (errno == EAGAIN || errno == EINTR)
				 continue;
			free(buf);
			buf = NULL;
			goto out;
		}
		total += bytes;
	}

	buf[total] = '\0';

out:
	if (fd >= 0)
		close(fd);
	return buf;
}