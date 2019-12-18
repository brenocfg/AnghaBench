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
typedef  scalar_t__ grant_ref_t ;

/* Variables and functions */
 scalar_t__ GNTTAB_LIST_END ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ gnttab_entry (scalar_t__) ; 

int
gnttab_claim_grant_reference(grant_ref_t *private_head)
{
	grant_ref_t g = *private_head;

	if (__predict_false(g == GNTTAB_LIST_END))
		return (g);
	*private_head = gnttab_entry(g);
	return (g);
}