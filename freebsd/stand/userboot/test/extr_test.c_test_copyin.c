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
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 

int
test_copyin(void *arg, const void *from, uint64_t to, size_t size)
{

	to &= 0x7fffffff;
	if (to > image_size)
		return (EFAULT);
	if (to + size > image_size)
		size = image_size - to;
	memcpy(&image[to], from, size);
	return(0);
}