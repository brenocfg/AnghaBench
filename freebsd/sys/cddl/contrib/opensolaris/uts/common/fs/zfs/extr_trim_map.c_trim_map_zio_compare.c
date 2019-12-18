#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ io_offset; scalar_t__ io_size; } ;
typedef  TYPE_1__ zio_t ;

/* Variables and functions */

__attribute__((used)) static int
trim_map_zio_compare(const void *x1, const void *x2)
{
	const zio_t *z1 = x1;
	const zio_t *z2 = x2;

	if (z1->io_offset < z2->io_offset) {
		if (z1->io_offset + z1->io_size > z2->io_offset)
			return (0);
		return (-1);
	}
	if (z1->io_offset > z2->io_offset) {
		if (z1->io_offset < z2->io_offset + z2->io_size)
			return (0);
		return (1);
	}
	return (0);
}