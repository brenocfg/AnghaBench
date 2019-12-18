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
typedef  size_t off_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int ftruncate (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  image_swap_fd ; 
 size_t image_swap_pgsz ; 
 size_t image_swap_size ; 
 size_t secsz ; 

__attribute__((used)) static off_t
image_swap_alloc(size_t size)
{
	off_t ofs;
	size_t unit;

	unit = (secsz > image_swap_pgsz) ? secsz : image_swap_pgsz;
	assert((unit & (unit - 1)) == 0);

	size = (size + unit - 1) & ~(unit - 1);

	ofs = image_swap_size;
	image_swap_size += size;
	if (ftruncate(image_swap_fd, image_swap_size) == -1) {
		image_swap_size = ofs;
		ofs = -1LL;
	}
	return (ofs);
}