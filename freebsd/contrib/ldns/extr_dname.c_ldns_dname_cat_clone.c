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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (int) ; 
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 int LDNS_XMALLOC (int,int) ; 
 int buf ; 
 scalar_t__ ldns_dname_last_label_is_root_label (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rdf_new_frm_data (scalar_t__,int,int) ; 
 int ldns_rdf_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int,int /*<<< orphan*/ ,int) ; 
 int uint8_t ; 

ldns_rdf *
ldns_dname_cat_clone(const ldns_rdf *rd1, const ldns_rdf *rd2)
{
	ldns_rdf *new;
	uint16_t new_size;
	uint8_t *buf;
	uint16_t left_size;

	if (ldns_rdf_get_type(rd1) != LDNS_RDF_TYPE_DNAME ||
			ldns_rdf_get_type(rd2) != LDNS_RDF_TYPE_DNAME) {
		return NULL;
	}

	/* remove root label if it is present at the end of the left
	 * rd, by reducing the size with 1
	 */
	left_size = ldns_rdf_size(rd1);
	if (ldns_dname_last_label_is_root_label(rd1)) {
		left_size--;
	}

	/* we overwrite the nullbyte of rd1 */
	new_size = left_size + ldns_rdf_size(rd2);
	buf = LDNS_XMALLOC(uint8_t, new_size);
	if (!buf) {
		return NULL;
	}

	/* put the two dname's after each other */
	memcpy(buf, ldns_rdf_data(rd1), left_size);
	memcpy(buf + left_size, ldns_rdf_data(rd2), ldns_rdf_size(rd2));

	new = ldns_rdf_new_frm_data(LDNS_RDF_TYPE_DNAME, new_size, buf);

	LDNS_FREE(buf);
	return new;
}