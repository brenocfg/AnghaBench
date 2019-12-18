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
 void* MAP_FAILED ; 
 void* mmap (void*,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmap_limit_check (size_t) ; 

void *xmmap_gently(void *start, size_t length,
		  int prot, int flags, int fd, off_t offset)
{
	void *ret;

	mmap_limit_check(length);
	ret = mmap(start, length, prot, flags, fd, offset);
	if (ret == MAP_FAILED && !length)
		ret = NULL;
	return ret;
}