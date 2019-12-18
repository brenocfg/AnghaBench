#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ hrtime_t ;
struct TYPE_3__ {scalar_t__ dtb_size; int dtb_flags; scalar_t__ dtb_switched; scalar_t__ dtb_offset; scalar_t__ dtb_interval; } ;
typedef  TYPE_1__ dtrace_buffer_t ;

/* Variables and functions */
 int DTRACEBUF_RING ; 
 int NCPU ; 

__attribute__((used)) static int
dtrace_buffer_consumed(dtrace_buffer_t *bufs, hrtime_t when)
{
	int i;

	for (i = 0; i < NCPU; i++) {
		dtrace_buffer_t *buf = &bufs[i];

		if (buf->dtb_size == 0)
			continue;

		if (buf->dtb_flags & DTRACEBUF_RING)
			return (0);

		if (!buf->dtb_switched && buf->dtb_offset != 0)
			return (0);

		if (buf->dtb_switched - buf->dtb_interval < when)
			return (0);
	}

	return (1);
}