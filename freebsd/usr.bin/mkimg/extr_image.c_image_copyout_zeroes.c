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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/ * calloc (int,size_t) ; 
 int image_copyout_memory (int,size_t,int /*<<< orphan*/ *) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t secsz ; 

int
image_copyout_zeroes(int fd, size_t count)
{
	static uint8_t *zeroes = NULL;
	size_t sz;
	int error;

	if (lseek(fd, (off_t)count, SEEK_CUR) != -1)
		return (0);

	/*
	 * If we can't seek, we must write.
	 */

	if (zeroes == NULL) {
		zeroes = calloc(1, secsz);
		if (zeroes == NULL)
			return (ENOMEM);
	}

	while (count > 0) {
		sz = (count > secsz) ? secsz : count;
		error = image_copyout_memory(fd, sz, zeroes);
		if (error)
			return (error);
		count -= sz;
	}
	return (0);
}