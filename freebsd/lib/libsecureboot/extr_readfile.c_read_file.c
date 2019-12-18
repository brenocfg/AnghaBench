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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 unsigned char* read_fd (int,size_t) ; 

unsigned char *
read_file(const char *path, size_t *len)
{
	struct stat st;
	unsigned char *ucp;
	int fd;

    	if (len)
		*len = 0;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	fstat(fd, &st);
	ucp = read_fd(fd, st.st_size);
	close(fd);
	if (len != NULL && ucp != NULL)
		*len = st.st_size;
	return (ucp);
}