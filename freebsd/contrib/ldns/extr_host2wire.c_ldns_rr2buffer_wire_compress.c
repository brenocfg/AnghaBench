#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rbtree_t ;
typedef  int /*<<< orphan*/  ldns_buffer ;
struct TYPE_2__ {scalar_t__ _compress; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_COMPRESS ; 
 int LDNS_SECTION_QUESTION ; 
 scalar_t__ ldns_buffer_position (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_buffer_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_write_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_buffer_write_u16_at (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ldns_buffer_write_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dname2buffer_wire_compress (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_wire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_wire_compress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* ldns_rr_descript (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_get_class (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_get_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rr_owner (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rr_rd_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_rdf (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  ldns_rr_ttl (int /*<<< orphan*/  const*) ; 

ldns_status
ldns_rr2buffer_wire_compress(ldns_buffer *buffer, const ldns_rr *rr, int section, ldns_rbtree_t *compression_data)
{
	uint16_t i;
	uint16_t rdl_pos = 0;

	if (ldns_rr_owner(rr)) {
		(void) ldns_dname2buffer_wire_compress(buffer, ldns_rr_owner(rr), compression_data);
	}
	
	if (ldns_buffer_reserve(buffer, 4)) {
		(void) ldns_buffer_write_u16(buffer, ldns_rr_get_type(rr));
		(void) ldns_buffer_write_u16(buffer, ldns_rr_get_class(rr));
	}

	if (section != LDNS_SECTION_QUESTION) {
		if (ldns_buffer_reserve(buffer, 6)) {
			ldns_buffer_write_u32(buffer, ldns_rr_ttl(rr));
			/* remember pos for later */
			rdl_pos = ldns_buffer_position(buffer);
			ldns_buffer_write_u16(buffer, 0);
		}
		if (LDNS_RR_COMPRESS ==
		    ldns_rr_descript(ldns_rr_get_type(rr))->_compress) {

			for (i = 0; i < ldns_rr_rd_count(rr); i++) {
				(void) ldns_rdf2buffer_wire_compress(buffer,
				    ldns_rr_rdf(rr, i), compression_data);
			}
		} else {
			for (i = 0; i < ldns_rr_rd_count(rr); i++) {
				(void) ldns_rdf2buffer_wire(
				    buffer, ldns_rr_rdf(rr, i));
			}
		}
		if (rdl_pos != 0) {
			ldns_buffer_write_u16_at(buffer, rdl_pos,
			                         ldns_buffer_position(buffer)
		        	                   - rdl_pos - 2);
		}
	}
	return ldns_buffer_status(buffer);
}