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
struct uni_sap {int /*<<< orphan*/  bhli; int /*<<< orphan*/  blli_id3; int /*<<< orphan*/  blli_id2; int /*<<< orphan*/  selector; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int unisve_is_catchall (struct uni_sap const*) ; 
 scalar_t__ unisve_overlap_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unisve_overlap_bhli (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unisve_overlap_blli_id2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unisve_overlap_blli_id3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unisve_overlap_selector (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
unisve_overlap_sap(const struct uni_sap *s1, const struct uni_sap *s2)
{
	int any1, any2;

	/*
	 * Two catch-all's SAP's are not allowed. A catch-all does never
	 * overlap with a non-catch all SAP.
	 */
	any1 = unisve_is_catchall(s1);
	any2 = unisve_is_catchall(s2);

	if (any1 && any2)
		return (1);
	 if(any1 || any2)
		return (0);

	return (unisve_overlap_addr(&s1->addr, &s2->addr) &&
	    unisve_overlap_selector(&s1->selector, &s2->selector) &&
	    unisve_overlap_blli_id2(&s1->blli_id2, &s2->blli_id2) &&
	    unisve_overlap_blli_id3(&s1->blli_id3, &s2->blli_id3) &&
	    unisve_overlap_bhli(&s1->bhli, &s2->bhli));
}