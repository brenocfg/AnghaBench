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
typedef  int /*<<< orphan*/  (* ldns_soa_serial_increment_func_t ) (int /*<<< orphan*/ ,void*) ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_INT32 ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  ldns_native2rdf_int32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rdf2native_int32 (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rdf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ldns_rr_set_rdf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 

void
ldns_rr_soa_increment_func_data(ldns_rr *soa, 
		ldns_soa_serial_increment_func_t f, void *data)
{
	ldns_rdf *prev_soa_serial_rdf;
	if ( !soa || !f || ldns_rr_get_type(soa) != LDNS_RR_TYPE_SOA 
			|| !ldns_rr_rdf(soa, 2)) {
		return;
	}
	prev_soa_serial_rdf = ldns_rr_set_rdf(
		  soa
		, ldns_native2rdf_int32(
			  LDNS_RDF_TYPE_INT32
			, (*f)( ldns_rdf2native_int32(
					ldns_rr_rdf(soa, 2))
			      , data
			)
		)
		, 2
	);
	LDNS_FREE(prev_soa_serial_rdf);
}