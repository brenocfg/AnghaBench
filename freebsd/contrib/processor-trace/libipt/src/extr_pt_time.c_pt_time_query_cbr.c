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
typedef  int /*<<< orphan*/  uint32_t ;
struct pt_time {int /*<<< orphan*/  cbr; int /*<<< orphan*/  have_cbr; } ;

/* Variables and functions */
 int pte_internal ; 
 int pte_no_cbr ; 

int pt_time_query_cbr(uint32_t *cbr, const struct pt_time *time)
{
	if (!cbr || !time)
		return -pte_internal;

	if (!time->have_cbr)
		return -pte_no_cbr;

	*cbr = time->cbr;

	return 0;
}