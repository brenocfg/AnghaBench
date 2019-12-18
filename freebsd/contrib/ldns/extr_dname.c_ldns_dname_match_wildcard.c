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
 scalar_t__ ldns_dname_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_dname_is_subdomain (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_dname_is_wildcard (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_dname_left_chop (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 

int
ldns_dname_match_wildcard(const ldns_rdf *dname, const ldns_rdf *wildcard)
{
	ldns_rdf *wc_chopped;
	int result;
	/* check whether it really is a wildcard */
	if (ldns_dname_is_wildcard(wildcard)) {
		/* ok, so the dname needs to be a subdomain of the wildcard
		 * without the *
		 */
		wc_chopped = ldns_dname_left_chop(wildcard);
		result = (int) ldns_dname_is_subdomain(dname, wc_chopped);
		ldns_rdf_deep_free(wc_chopped);
	} else {
		result = (ldns_dname_compare(dname, wildcard) == 0);
	}
	return result;
}