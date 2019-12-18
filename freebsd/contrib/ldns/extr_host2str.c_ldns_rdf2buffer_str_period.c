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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_WIRE_RDATA_ERR ; 
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 int ldns_rdf_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_read_uint32 (int /*<<< orphan*/ ) ; 

ldns_status
ldns_rdf2buffer_str_period(ldns_buffer *output, const ldns_rdf *rdf)
{
	/* period is the number of seconds */
	if (ldns_rdf_size(rdf) != 4) {
		return LDNS_STATUS_WIRE_RDATA_ERR;
	}
	ldns_buffer_printf(output, "%u", ldns_read_uint32(ldns_rdf_data(rdf)));
	return ldns_buffer_status(output);
}