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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_DNAME_NORMALIZE (int) ; 
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 scalar_t__ ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_size (int /*<<< orphan*/  const*) ; 

void
ldns_dname2canonical(const ldns_rdf *rd)
{
	uint8_t *rdd;
	uint16_t i;

	if (ldns_rdf_get_type(rd) != LDNS_RDF_TYPE_DNAME) {
		return;
	}

	rdd = (uint8_t*)ldns_rdf_data(rd);
	for (i = 0; i < ldns_rdf_size(rd); i++, rdd++) {
		*rdd = (uint8_t)LDNS_DNAME_NORMALIZE((int)*rdd);
	}
}