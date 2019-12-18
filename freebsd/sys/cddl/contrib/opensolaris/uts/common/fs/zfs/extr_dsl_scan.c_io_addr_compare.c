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
struct TYPE_2__ {scalar_t__ sio_offset; } ;
typedef  TYPE_1__ scan_io_t ;

/* Variables and functions */

__attribute__((used)) static int
io_addr_compare(const void *x, const void *y)
{
	const scan_io_t *a = x, *b = y;

	if (a->sio_offset < b->sio_offset)
		return (-1);
	if (a->sio_offset == b->sio_offset)
		return (0);
	return (1);
}