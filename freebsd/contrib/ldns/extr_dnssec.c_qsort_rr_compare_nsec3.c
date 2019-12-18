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
typedef  int /*<<< orphan*/  ldns_rr ;

/* Variables and functions */
 int ldns_rdf_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/  const*) ; 

int
qsort_rr_compare_nsec3(const void *a, const void *b)
{
	const ldns_rr *rr1 = * (const ldns_rr **) a;
	const ldns_rr *rr2 = * (const ldns_rr **) b;
	if (rr1 == NULL && rr2 == NULL) {
		return 0;
	}
	if (rr1 == NULL) {
		return -1;
	}
	if (rr2 == NULL) {
		return 1;
	}
	return ldns_rdf_compare(ldns_rr_owner(rr1), ldns_rr_owner(rr2));
}