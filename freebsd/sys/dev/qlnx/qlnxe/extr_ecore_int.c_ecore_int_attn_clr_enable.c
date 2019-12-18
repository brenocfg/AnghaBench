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
struct ecore_dev {int attn_clr_en; } ;

/* Variables and functions */

void ecore_int_attn_clr_enable(struct ecore_dev *p_dev, bool clr_enable)
{
	p_dev->attn_clr_en = clr_enable;
}