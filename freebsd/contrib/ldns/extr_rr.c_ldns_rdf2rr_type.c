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
typedef  scalar_t__ ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_TYPE_TYPE ; 
 scalar_t__ ldns_rdf2native_int16 (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 

ldns_rr_type
ldns_rdf2rr_type(const ldns_rdf *rd)
{
        ldns_rr_type r;

        if (!rd) {
                return 0;
        }

        if (ldns_rdf_get_type(rd) != LDNS_RDF_TYPE_TYPE) {
                return 0;
        }

        r = (ldns_rr_type) ldns_rdf2native_int16(rd);
        return r;
}