#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  banner; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 size_t atomicio (int /*<<< orphan*/ ,int,char*,size_t) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat (int,struct stat*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ options ; 
 int /*<<< orphan*/  read ; 
 char* xmalloc (size_t) ; 

char *
auth2_read_banner(void)
{
	struct stat st;
	char *banner = NULL;
	size_t len, n;
	int fd;

	if ((fd = open(options.banner, O_RDONLY)) == -1)
		return (NULL);
	if (fstat(fd, &st) == -1) {
		close(fd);
		return (NULL);
	}
	if (st.st_size <= 0 || st.st_size > 1*1024*1024) {
		close(fd);
		return (NULL);
	}

	len = (size_t)st.st_size;		/* truncate */
	banner = xmalloc(len + 1);
	n = atomicio(read, fd, banner, len);
	close(fd);

	if (n != len) {
		free(banner);
		return (NULL);
	}
	banner[n] = '\0';

	return (banner);
}