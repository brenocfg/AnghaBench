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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct pt_time {int /*<<< orphan*/  have_tsc; int /*<<< orphan*/  lost_cyc; int /*<<< orphan*/  lost_mtc; int /*<<< orphan*/  tsc; } ;

/* Variables and functions */
 int pte_internal ; 
 int pte_no_time ; 

int pt_time_query_tsc(uint64_t *tsc, uint32_t *lost_mtc,
		      uint32_t *lost_cyc, const struct pt_time *time)
{
	if (!tsc || !time)
		return -pte_internal;

	*tsc = time->tsc;

	if (lost_mtc)
		*lost_mtc = time->lost_mtc;
	if (lost_cyc)
		*lost_cyc = time->lost_cyc;

	if (!time->have_tsc)
		return -pte_no_time;

	return 0;
}