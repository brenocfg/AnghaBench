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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_DNAME_NORMALIZE (int) ; 
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t ldns_dname_label_count (int /*<<< orphan*/  const*) ; 
 int* ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 

int
ldns_dname_compare(const ldns_rdf *dname1, const ldns_rdf *dname2)
{
	size_t lc1, lc2, lc1f, lc2f;
	size_t i;
	int result = 0;
	uint8_t *lp1, *lp2;

	/* see RFC4034 for this algorithm */
	/* this algorithm assumes the names are normalized to case */

        /* only when both are not NULL we can say anything about them */
        if (!dname1 && !dname2) {
                return 0;
        }
        if (!dname1 || !dname2) {
                return -1;
        }
	/* asserts must happen later as we are looking in the
	 * dname, which could be NULL. But this case is handled
	 * above
	 */
	assert(ldns_rdf_get_type(dname1) == LDNS_RDF_TYPE_DNAME);
	assert(ldns_rdf_get_type(dname2) == LDNS_RDF_TYPE_DNAME);

	lc1 = ldns_dname_label_count(dname1);
	lc2 = ldns_dname_label_count(dname2);

	if (lc1 == 0 && lc2 == 0) {
		return 0;
	}
	if (lc1 == 0) {
		return -1;
	}
	if (lc2 == 0) {
		return 1;
	}
	lc1--;
	lc2--;
	/* we start at the last label */
	while (true) {
		/* find the label first */
		lc1f = lc1;
		lp1 = ldns_rdf_data(dname1);
		while (lc1f > 0) {
			lp1 += *lp1 + 1;
			lc1f--;
		}

		/* and find the other one */
		lc2f = lc2;
		lp2 = ldns_rdf_data(dname2);
		while (lc2f > 0) {
			lp2 += *lp2 + 1;
			lc2f--;
		}

		/* now check the label character for character. */
		for (i = 1; i < (size_t)(*lp1 + 1); i++) {
			if (i > *lp2) {
				/* apparently label 1 is larger */
				result = 1;
				goto done;
			}
			if (LDNS_DNAME_NORMALIZE((int) *(lp1 + i)) <
			    LDNS_DNAME_NORMALIZE((int) *(lp2 + i))) {
			    result = -1;
			    goto done;
			} else if (LDNS_DNAME_NORMALIZE((int) *(lp1 + i)) >
			    LDNS_DNAME_NORMALIZE((int) *(lp2 + i))) {
			    result = 1;
			    goto done;
			}
		}
		if (*lp1 < *lp2) {
			/* apparently label 2 is larger */
			result = -1;
			goto done;
		}
		if (lc1 == 0 && lc2 > 0) {
			result = -1;
			goto done;
		} else if (lc1 > 0 && lc2 == 0) {
			result = 1;
			goto done;
		} else if (lc1 == 0 && lc2 == 0) {
			result = 0;
			goto done;
		}
		lc1--;
		lc2--;
	}

	done:
	return result;
}