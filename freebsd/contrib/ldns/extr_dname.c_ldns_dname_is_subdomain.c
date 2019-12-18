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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  const ldns_rdf ;
typedef  scalar_t__ int8_t ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 int /*<<< orphan*/  ldns_dname2canonical (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* ldns_dname_clone_from (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* ldns_dname_label (int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ ldns_dname_label_count (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 

bool
ldns_dname_is_subdomain(const ldns_rdf *sub, const ldns_rdf *parent)
{
	uint8_t sub_lab;
	uint8_t par_lab;
	int8_t i, j;
	ldns_rdf *tmp_sub = NULL;
	ldns_rdf *tmp_par = NULL;
    ldns_rdf *sub_clone;
    ldns_rdf *parent_clone;
    bool result = true;

	if (ldns_rdf_get_type(sub) != LDNS_RDF_TYPE_DNAME ||
			ldns_rdf_get_type(parent) != LDNS_RDF_TYPE_DNAME ||
			ldns_rdf_compare(sub, parent) == 0) {
		return false;
	}

    /* would be nicer if we do not have to clone... */
    sub_clone = ldns_dname_clone_from(sub, 0);
    parent_clone = ldns_dname_clone_from(parent, 0);
    ldns_dname2canonical(sub_clone);
    ldns_dname2canonical(parent_clone);

	sub_lab = ldns_dname_label_count(sub_clone);
	par_lab = ldns_dname_label_count(parent_clone);

	/* if sub sits above parent, it cannot be a child/sub domain */
	if (sub_lab < par_lab) {
		result = false;
	} else {
		/* check all labels the from the parent labels, from right to left.
		 * When they /all/ match we have found a subdomain
		 */
		j = sub_lab - 1; /* we count from zero, thank you */
		for (i = par_lab -1; i >= 0; i--) {
			tmp_sub = ldns_dname_label(sub_clone, j);
			tmp_par = ldns_dname_label(parent_clone, i);
			if (!tmp_sub || !tmp_par) {
				/* deep free does null check */
				ldns_rdf_deep_free(tmp_sub);
				ldns_rdf_deep_free(tmp_par);
				result = false;
				break;
			}

			if (ldns_rdf_compare(tmp_sub, tmp_par) != 0) {
				/* they are not equal */
				ldns_rdf_deep_free(tmp_sub);
				ldns_rdf_deep_free(tmp_par);
				result = false;
				break;
			}
			ldns_rdf_deep_free(tmp_sub);
			ldns_rdf_deep_free(tmp_par);
			j--;
		}
	}
	ldns_rdf_deep_free(sub_clone);
	ldns_rdf_deep_free(parent_clone);
	return result;
}