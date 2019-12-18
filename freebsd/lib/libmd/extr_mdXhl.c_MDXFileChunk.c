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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 char* MDXFdChunk (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

char *
MDXFileChunk(const char *filename, char *buf, off_t ofs, off_t len)
{
	char *ret;
	int e, fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return NULL;
	ret = MDXFdChunk(fd, buf, ofs, len);
	e = errno;
	close (fd);
	errno = e;
	return ret;
}