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
struct pt_time_cal {unsigned long long tsc; unsigned long long cyc_tsc; unsigned long long cyc_mtc; scalar_t__ have_mtc; scalar_t__ ctc; } ;
struct pt_config {int dummy; } ;

/* Variables and functions */
 int pte_internal ; 

int pt_tcal_update_ovf(struct pt_time_cal *tcal,
		       const struct pt_config *config)
{
	if (!tcal || !config)
		return -pte_internal;

	tcal->tsc = 0ull;
	tcal->cyc_tsc = 0ull;
	tcal->cyc_mtc = 0ull;
	tcal->ctc = 0;
	tcal->have_mtc = 0;

	return 0;
}