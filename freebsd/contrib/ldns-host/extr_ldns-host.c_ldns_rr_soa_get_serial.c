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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_TYPE_INT32 ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  ldns_rdf2native_int32 (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 
 int ldns_rdf_size (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/  const*) ; 
 int ldns_rr_rd_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static uint32_t
ldns_rr_soa_get_serial(const ldns_rr *rr)
{
    const ldns_rdf *rdf;
  
    if (ldns_rr_get_type(rr) != LDNS_RR_TYPE_SOA) return 0;
    if (ldns_rr_rd_count(rr) != 7) return 0;
    rdf = ldns_rr_rdf(rr, 2);
    if (ldns_rdf_get_type(rdf) != LDNS_RDF_TYPE_INT32) return 0;
    if (ldns_rdf_size(rdf) != 4) return 0;
    return ldns_rdf2native_int32(rdf);
}