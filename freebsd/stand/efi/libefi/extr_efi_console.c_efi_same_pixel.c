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
struct TYPE_2__ {scalar_t__ ta_format; scalar_t__ ta_fgcolor; scalar_t__ ta_bgcolor; } ;
struct text_pixel {scalar_t__ c; TYPE_1__ a; } ;

/* Variables and functions */

__attribute__((used)) static bool
efi_same_pixel(struct text_pixel *px1, struct text_pixel *px2)
{
	if (px1->c != px2->c)
		return (false);

	if (px1->a.ta_format != px2->a.ta_format)
		return (false);
	if (px1->a.ta_fgcolor != px2->a.ta_fgcolor)
		return (false);
	if (px1->a.ta_bgcolor != px2->a.ta_bgcolor)
		return (false);

	return (true);
}