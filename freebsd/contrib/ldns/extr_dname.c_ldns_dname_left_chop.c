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
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 scalar_t__ ldns_dname_label_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_dname_new_frm_data (int,int*) ; 
 int* ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 
 int ldns_rdf_size (int /*<<< orphan*/  const*) ; 

ldns_rdf *
ldns_dname_left_chop(const ldns_rdf *d)
{
	uint8_t label_pos;
	ldns_rdf *chop;

	if (!d) {
		return NULL;
	}

	if (ldns_rdf_get_type(d) != LDNS_RDF_TYPE_DNAME) {
		return NULL;
	}
	if (ldns_dname_label_count(d) == 0) {
		/* root label */
		return NULL;
	}
	/* 05blaat02nl00 */
	label_pos = ldns_rdf_data(d)[0];

	chop = ldns_dname_new_frm_data(ldns_rdf_size(d) - label_pos - 1,
			ldns_rdf_data(d) + label_pos + 1);
	return chop;
}