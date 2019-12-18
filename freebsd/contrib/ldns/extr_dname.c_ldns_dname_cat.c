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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  const ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  LDNS_XREALLOC (scalar_t__,int,scalar_t__) ; 
 scalar_t__ ldns_dname_last_label_is_root_label (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf_set_data (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ldns_rdf_set_size (int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ ldns_rdf_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 int newd ; 
 int uint8_t ; 

ldns_status
ldns_dname_cat(ldns_rdf *rd1, const ldns_rdf *rd2)
{
	uint16_t left_size;
	uint16_t size;
	uint8_t* newd;

	if (ldns_rdf_get_type(rd1) != LDNS_RDF_TYPE_DNAME ||
			ldns_rdf_get_type(rd2) != LDNS_RDF_TYPE_DNAME) {
		return LDNS_STATUS_ERR;
	}

	/* remove root label if it is present at the end of the left
	 * rd, by reducing the size with 1
	 */
	left_size = ldns_rdf_size(rd1);
	if (ldns_dname_last_label_is_root_label(rd1)) {
		left_size--;
	}

	size = left_size + ldns_rdf_size(rd2);
	newd = LDNS_XREALLOC(ldns_rdf_data(rd1), uint8_t, size);
	if(!newd) {
		return LDNS_STATUS_MEM_ERR;
	}

	ldns_rdf_set_data(rd1, newd);
	memcpy(ldns_rdf_data(rd1) + left_size, ldns_rdf_data(rd2),
			ldns_rdf_size(rd2));
	ldns_rdf_set_size(rd1, size);

	return LDNS_STATUS_OK;
}