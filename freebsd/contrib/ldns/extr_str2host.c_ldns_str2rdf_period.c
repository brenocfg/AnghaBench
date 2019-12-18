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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RDF_TYPE_PERIOD ; 
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 scalar_t__ htonl (scalar_t__) ; 
 int /*<<< orphan*/ * ldns_rdf_new_frm_data (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ ldns_str2period (char const*,char const**) ; 

ldns_status
ldns_str2rdf_period(ldns_rdf **rd,const char *period)
{
        uint32_t p;
        const char *end;

        /* Allocate required space... */
        p = ldns_str2period(period, &end);

        if (*end != 0) {
		return LDNS_STATUS_ERR;
        } else {
                p = (uint32_t) htonl(p);
		*rd = ldns_rdf_new_frm_data(
			LDNS_RDF_TYPE_PERIOD, sizeof(uint32_t), &p);
        }
	return *rd?LDNS_STATUS_OK:LDNS_STATUS_MEM_ERR;
}