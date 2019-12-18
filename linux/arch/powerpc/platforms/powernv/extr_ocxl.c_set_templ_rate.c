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

/* Variables and functions */
 unsigned int PNV_OCXL_TL_MAX_TEMPLATE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void set_templ_rate(unsigned int templ, unsigned int rate, char *buf)
{
	int shift, idx;

	WARN_ON(templ > PNV_OCXL_TL_MAX_TEMPLATE);
	idx = (PNV_OCXL_TL_MAX_TEMPLATE - templ) / 2;
	shift = 4 * (1 - ((PNV_OCXL_TL_MAX_TEMPLATE - templ) % 2));
	buf[idx] |= rate << shift;
}