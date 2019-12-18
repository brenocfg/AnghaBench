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
typedef  size_t uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 scalar_t__ ldns_dname_label_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_dname_new_frm_data (size_t,size_t*) ; 
 size_t* ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 
 size_t ldns_rdf_size (int /*<<< orphan*/  const*) ; 

ldns_rdf *
ldns_dname_clone_from(const ldns_rdf *d, uint16_t n)
{
	uint8_t *data;
	uint8_t label_size;
	size_t data_size;

	if (!d ||
	    ldns_rdf_get_type(d) != LDNS_RDF_TYPE_DNAME ||
	    ldns_dname_label_count(d) < n) {
		return NULL;
	}

	data = ldns_rdf_data(d);
	data_size = ldns_rdf_size(d);
	while (n > 0) {
		label_size = data[0] + 1;
		data += label_size;
		if (data_size < label_size) {
			/* this label is very broken */
			return NULL;
		}
		data_size -= label_size;
		n--;
	}

	return ldns_dname_new_frm_data(data_size, data);
}