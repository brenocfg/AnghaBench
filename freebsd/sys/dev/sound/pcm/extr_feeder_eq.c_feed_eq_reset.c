#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_4__ {scalar_t__* o2; scalar_t__* o1; scalar_t__* i2; scalar_t__* i1; } ;
struct TYPE_3__ {scalar_t__* o2; scalar_t__* o1; scalar_t__* i2; scalar_t__* i1; } ;
struct feed_eq_info {size_t channels; TYPE_2__ bass; TYPE_1__ treble; } ;

/* Variables and functions */

__attribute__((used)) static void
feed_eq_reset(struct feed_eq_info *info)
{
	uint32_t i;

	for (i = 0; i < info->channels; i++) {
		info->treble.i1[i] = 0;
		info->treble.i2[i] = 0;
		info->treble.o1[i] = 0;
		info->treble.o2[i] = 0;
		info->bass.i1[i] = 0;
		info->bass.i2[i] = 0;
		info->bass.o1[i] = 0;
		info->bass.o2[i] = 0;
	}
}