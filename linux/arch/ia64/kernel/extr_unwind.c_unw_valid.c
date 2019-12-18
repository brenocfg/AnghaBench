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
struct TYPE_4__ {unsigned long top; unsigned long limit; } ;
struct TYPE_3__ {unsigned long limit; unsigned long top; } ;
struct unw_frame_info {TYPE_2__ memstk; TYPE_1__ regstk; } ;

/* Variables and functions */

__attribute__((used)) static int
unw_valid(const struct unw_frame_info *info, unsigned long* p)
{
	unsigned long loc = (unsigned long)p;
	return (loc >= info->regstk.limit && loc < info->regstk.top) ||
	       (loc >= info->memstk.top && loc < info->memstk.limit);
}