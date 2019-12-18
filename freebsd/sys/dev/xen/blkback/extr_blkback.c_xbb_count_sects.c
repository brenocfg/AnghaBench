#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int8_t ;
struct TYPE_5__ {int nr_segments; TYPE_1__* seg; } ;
typedef  TYPE_2__ blkif_request_t ;
struct TYPE_4__ {scalar_t__ first_sect; scalar_t__ last_sect; } ;

/* Variables and functions */

__attribute__((used)) static __inline int
xbb_count_sects(blkif_request_t *ring_req)
{
	int i;
	int cur_size = 0;

	for (i = 0; i < ring_req->nr_segments; i++) {
		int nsect;

		nsect = (int8_t)(ring_req->seg[i].last_sect -
			ring_req->seg[i].first_sect + 1);
		if (nsect <= 0)
			break;

		cur_size += nsect;
	}

	return (cur_size);
}