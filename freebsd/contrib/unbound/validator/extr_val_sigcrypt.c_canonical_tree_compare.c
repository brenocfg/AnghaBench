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
struct canon_rr {scalar_t__ rrset; int /*<<< orphan*/  rr_idx; } ;

/* Variables and functions */
 int canonical_compare (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (int) ; 

int
canonical_tree_compare(const void* k1, const void* k2)
{
	struct canon_rr* r1 = (struct canon_rr*)k1;
	struct canon_rr* r2 = (struct canon_rr*)k2;
	log_assert(r1->rrset == r2->rrset);
	return canonical_compare(r1->rrset, r1->rr_idx, r2->rr_idx);
}