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
struct TYPE_2__ {int byte1; } ;
union ses_elm_sas_hdr {TYPE_1__ type0_noneip; } ;

/* Variables and functions */

int
ses_elm_sas_type0_not_all_phys(union ses_elm_sas_hdr *hdr)
{
	return ((hdr)->type0_noneip.byte1 & 0x1);
}