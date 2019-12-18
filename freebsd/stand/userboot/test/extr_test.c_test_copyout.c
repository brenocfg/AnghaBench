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
typedef  int uint64_t ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/ * image ; 
 int image_size ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 

int
test_copyout(void *arg, uint64_t from, void *to, size_t size)
{

	from &= 0x7fffffff;
	if (from > image_size)
		return (EFAULT);
	if (from + size > image_size)
		size = image_size - from;
	memcpy(to, &image[from], size);
	return(0);
}