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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ldns_rr ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 scalar_t__ LDNS_RR_TYPE_NSEC3PARAM ; 
 int /*<<< orphan*/  ldns_rdf2native_int16 (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rdf_size (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (int /*<<< orphan*/  const*,int) ; 

uint16_t
ldns_nsec3_iterations(const ldns_rr *nsec3_rr)
{
	if (nsec3_rr &&
	      (ldns_rr_get_type(nsec3_rr) == LDNS_RR_TYPE_NSEC3 ||
	       ldns_rr_get_type(nsec3_rr) == LDNS_RR_TYPE_NSEC3PARAM)
	    && (ldns_rr_rdf(nsec3_rr, 2) != NULL)
	    && ldns_rdf_size(ldns_rr_rdf(nsec3_rr, 2)) > 0) {
		return ldns_rdf2native_int16(ldns_rr_rdf(nsec3_rr, 2));
	}
	return 0;
	
}