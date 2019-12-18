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
typedef  int /*<<< orphan*/  vdev_label_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int VDEV_LABELS ; 

__attribute__((used)) static uint64_t
vdev_label_offset(uint64_t psize, int l, uint64_t offset)
{
	uint64_t label_offset;

	if (l < VDEV_LABELS / 2)
		label_offset = 0;
	else
		label_offset = psize - VDEV_LABELS * sizeof (vdev_label_t);

	return (offset + l * sizeof (vdev_label_t) + label_offset);
}