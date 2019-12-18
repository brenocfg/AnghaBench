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
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_wire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_rd_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_rdf (int /*<<< orphan*/  const*,scalar_t__) ; 

ldns_status
ldns_rr_rdata2buffer_wire(ldns_buffer *buffer, const ldns_rr *rr)
{
	uint16_t i;

	/* convert all the rdf's */
	for (i = 0; i < ldns_rr_rd_count(rr); i++) {
		(void) ldns_rdf2buffer_wire(buffer, ldns_rr_rdf(rr,i));
	}
	return ldns_buffer_status(buffer);
}