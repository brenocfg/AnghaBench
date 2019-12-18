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
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  free (void*) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ read (int,void*,size_t) ; 

void *
alloc_pread(int fd, off_t off, size_t len)
{
	void *buf;

	buf = malloc(len);
	if (buf == NULL) {
#ifdef DEBUG
		printf("\nmalloc(%d) failed\n", (int)len);
#endif
		return (NULL);
	}
	if (lseek(fd, off, SEEK_SET) == -1) {
#ifdef DEBUG
		printf("\nlseek failed\n");
#endif
		free(buf);
		return (NULL);
	}
	if ((size_t)read(fd, buf, len) != len) {
#ifdef DEBUG
		printf("\nread failed\n");
#endif
		free(buf);
		return (NULL);
	}
	return (buf);
}