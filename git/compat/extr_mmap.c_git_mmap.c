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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 void* xmalloc (size_t) ; 
 scalar_t__ xpread (int,char*,size_t,scalar_t__) ; 

void *git_mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset)
{
	size_t n = 0;

	if (start != NULL || flags != MAP_PRIVATE || prot != PROT_READ)
		die("Invalid usage of mmap when built with NO_MMAP");

	start = xmalloc(length);
	if (start == NULL) {
		errno = ENOMEM;
		return MAP_FAILED;
	}

	while (n < length) {
		ssize_t count = xpread(fd, (char *)start + n, length - n, offset + n);

		if (count == 0) {
			memset((char *)start+n, 0, length-n);
			break;
		}

		if (count < 0) {
			free(start);
			errno = EACCES;
			return MAP_FAILED;
		}

		n += count;
	}

	return start;
}