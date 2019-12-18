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
struct sglist {int sg_nseg; TYPE_1__* sg_segs; } ;
struct TYPE_2__ {scalar_t__ ss_len; } ;

/* Variables and functions */

size_t
sglist_length(struct sglist *sg)
{
	size_t space;
	int i;

	space = 0;
	for (i = 0; i < sg->sg_nseg; i++)
		space += sg->sg_segs[i].ss_len;
	return (space);
}