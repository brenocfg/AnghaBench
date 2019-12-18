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
struct pt_time_cal {int check_skl168; } ;
struct TYPE_2__ {scalar_t__ skl168; } ;
struct pt_config {TYPE_1__ errata; } ;

/* Variables and functions */
 int pte_internal ; 

int pt_tcal_update_psb(struct pt_time_cal *tcal,
		       const struct pt_config *config)
{
	if (!tcal || !config)
		return -pte_internal;

	if (config->errata.skl168)
		tcal->check_skl168 = 1;

	return 0;
}