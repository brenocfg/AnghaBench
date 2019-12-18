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
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 int /*<<< orphan*/  assert (int) ; 
 int ldns_dname_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 

int
ldns_dname_interval(const ldns_rdf *prev, const ldns_rdf *middle,
		const ldns_rdf *next)
{
	int prev_check, next_check;

	assert(ldns_rdf_get_type(prev) == LDNS_RDF_TYPE_DNAME);
	assert(ldns_rdf_get_type(middle) == LDNS_RDF_TYPE_DNAME);
	assert(ldns_rdf_get_type(next) == LDNS_RDF_TYPE_DNAME);

	prev_check = ldns_dname_compare(prev, middle);
	next_check = ldns_dname_compare(middle, next);
	/* <= next. This cannot be the case for nsec, because then we would
	 * have gotten the nsec of next...
	 */
	if (next_check == 0) {
		return 0;
	}

			/* <= */
	if ((prev_check == -1 || prev_check == 0) &&
			/* < */
			next_check == -1) {
		return -1;
	} else {
		return 1;
	}
}