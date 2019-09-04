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
typedef  long uint32_t ;
typedef  unsigned int git_off_t ;
typedef  int /*<<< orphan*/  git_mwindow_file ;
typedef  int /*<<< orphan*/  git_mwindow ;

/* Variables and functions */
 void* Z_NULL ; 
 long crc32 (long,void*,unsigned int) ; 
 int /*<<< orphan*/  git_mwindow_close (int /*<<< orphan*/ **) ; 
 void* git_mwindow_open (int /*<<< orphan*/ *,int /*<<< orphan*/ **,unsigned int,size_t,unsigned int*) ; 
 long htonl (long) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static int crc_object(uint32_t *crc_out, git_mwindow_file *mwf, git_off_t start, git_off_t size)
{
	void *ptr;
	uint32_t crc;
	unsigned int left, len;
	git_mwindow *w = NULL;

	crc = crc32(0L, Z_NULL, 0);
	while (size) {
		ptr = git_mwindow_open(mwf, &w, start, (size_t)size, &left);
		if (ptr == NULL)
			return -1;

		len = min(left, (unsigned int)size);
		crc = crc32(crc, ptr, len);
		size -= len;
		start += len;
		git_mwindow_close(&w);
	}

	*crc_out = htonl(crc);
	return 0;
}