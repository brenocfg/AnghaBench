#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rbtree_t ;
struct TYPE_14__ {int /*<<< orphan*/  _edns_data; } ;
typedef  TYPE_1__ ldns_pkt ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RDF_TYPE_DNAME ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_OPT ; 
 int /*<<< orphan*/  LDNS_SECTION_ADDITIONAL ; 
 int /*<<< orphan*/  LDNS_SECTION_ANSWER ; 
 int /*<<< orphan*/  LDNS_SECTION_AUTHORITY ; 
 int /*<<< orphan*/  LDNS_SECTION_QUESTION ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  compression_node_free ; 
 scalar_t__ ldns_dname_compare ; 
 int /*<<< orphan*/  ldns_hdr2buffer_wire (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/ * ldns_pkt_additional (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * ldns_pkt_answer (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * ldns_pkt_authority (TYPE_1__ const*) ; 
 scalar_t__ ldns_pkt_edns (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_edns_extended_rcode (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_edns_udp_size (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_edns_version (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_edns_z (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * ldns_pkt_question (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * ldns_pkt_tsig (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * ldns_rbtree_create (int (*) (void const*,void const*)) ; 
 int /*<<< orphan*/  ldns_rbtree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_new_frm_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ldns_read_uint32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr2buffer_wire_compress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_new () ; 
 int /*<<< orphan*/  ldns_rr_pop_rdf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_push_rdf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_ttl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_traverse_postorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_write_uint16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ldns_status
ldns_pkt2buffer_wire(ldns_buffer *buffer, const ldns_pkt *packet)
{
	ldns_rr_list *rr_list;
	uint16_t i;

	/* edns tmp vars */
	ldns_rr *edns_rr;
	uint8_t edata[4];

	ldns_rbtree_t *compression_data = ldns_rbtree_create((int (*)(const void *, const void *))ldns_dname_compare);
	
	(void) ldns_hdr2buffer_wire(buffer, packet);

	rr_list = ldns_pkt_question(packet);
	if (rr_list) {
		for (i = 0; i < ldns_rr_list_rr_count(rr_list); i++) {
			(void) ldns_rr2buffer_wire_compress(buffer, 
			             ldns_rr_list_rr(rr_list, i), LDNS_SECTION_QUESTION, compression_data);
		}
	}
	rr_list = ldns_pkt_answer(packet);
	if (rr_list) {
		for (i = 0; i < ldns_rr_list_rr_count(rr_list); i++) {
			(void) ldns_rr2buffer_wire_compress(buffer, 
			             ldns_rr_list_rr(rr_list, i), LDNS_SECTION_ANSWER, compression_data);
		}
	}
	rr_list = ldns_pkt_authority(packet);
	if (rr_list) {
		for (i = 0; i < ldns_rr_list_rr_count(rr_list); i++) {
			(void) ldns_rr2buffer_wire_compress(buffer, 
			             ldns_rr_list_rr(rr_list, i), LDNS_SECTION_AUTHORITY, compression_data);
		}
	}
	rr_list = ldns_pkt_additional(packet);
	if (rr_list) {
		for (i = 0; i < ldns_rr_list_rr_count(rr_list); i++) {
			(void) ldns_rr2buffer_wire_compress(buffer, 
			             ldns_rr_list_rr(rr_list, i), LDNS_SECTION_ADDITIONAL, compression_data);
		}
	}
	
	/* add EDNS to additional if it is needed */
	if (ldns_pkt_edns(packet)) {
		edns_rr = ldns_rr_new();
		if(!edns_rr) return LDNS_STATUS_MEM_ERR;
		ldns_rr_set_owner(edns_rr,
				ldns_rdf_new_frm_str(LDNS_RDF_TYPE_DNAME, "."));
		ldns_rr_set_type(edns_rr, LDNS_RR_TYPE_OPT);
		ldns_rr_set_class(edns_rr, ldns_pkt_edns_udp_size(packet));
		edata[0] = ldns_pkt_edns_extended_rcode(packet);
		edata[1] = ldns_pkt_edns_version(packet);
		ldns_write_uint16(&edata[2], ldns_pkt_edns_z(packet));
		ldns_rr_set_ttl(edns_rr, ldns_read_uint32(edata));
		/* don't forget to add the edns rdata (if any) */
		if (packet->_edns_data)
			ldns_rr_push_rdf (edns_rr, packet->_edns_data);
		(void)ldns_rr2buffer_wire_compress(buffer, edns_rr, LDNS_SECTION_ADDITIONAL, compression_data);
		/* take the edns rdata back out of the rr before we free rr */
		if (packet->_edns_data)
			(void)ldns_rr_pop_rdf (edns_rr);
		ldns_rr_free(edns_rr);
	}
	
	/* add TSIG to additional if it is there */
	if (ldns_pkt_tsig(packet)) {
		(void) ldns_rr2buffer_wire_compress(buffer,
		                           ldns_pkt_tsig(packet), LDNS_SECTION_ADDITIONAL, compression_data);
	}

	ldns_traverse_postorder(compression_data,compression_node_free,NULL);
	ldns_rbtree_free(compression_data);

	return LDNS_STATUS_OK;
}