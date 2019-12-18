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
struct serviced_query {scalar_t__ status; int dnssec; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; int /*<<< orphan*/  opt_list; int /*<<< orphan*/  qbuflen; int /*<<< orphan*/  qbuf; TYPE_1__* outnet; int /*<<< orphan*/  nocaps; } ;
struct edns_data {int edns_present; int bits; scalar_t__ udp_size; int /*<<< orphan*/  opt_list; int /*<<< orphan*/  edns_version; scalar_t__ ext_rcode; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_2__ {int /*<<< orphan*/  rnd; scalar_t__ use_caps_for_id; } ;

/* Variables and functions */
 int BIT_CD ; 
 scalar_t__ EDNS_ADVERTISED_SIZE ; 
 int /*<<< orphan*/  EDNS_ADVERTISED_VERSION ; 
 int EDNS_DO ; 
 scalar_t__ EDNS_FRAG_SIZE_IP4 ; 
 scalar_t__ EDNS_FRAG_SIZE_IP6 ; 
 int /*<<< orphan*/  LDNS_CD_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ addr_is_ip6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attach_edns_record (int /*<<< orphan*/ *,struct edns_data*) ; 
 int /*<<< orphan*/  serviced_perturb_qname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ serviced_query_UDP_EDNS_FRAG ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
serviced_encode(struct serviced_query* sq, sldns_buffer* buff, int with_edns)
{
	/* if we are using 0x20 bits for ID randomness, perturb them */
	if(sq->outnet->use_caps_for_id && !sq->nocaps) {
		serviced_perturb_qname(sq->outnet->rnd, sq->qbuf, sq->qbuflen);
	}
	/* generate query */
	sldns_buffer_clear(buff);
	sldns_buffer_write_u16(buff, 0); /* id placeholder */
	sldns_buffer_write(buff, sq->qbuf, sq->qbuflen);
	sldns_buffer_flip(buff);
	if(with_edns) {
		/* add edns section */
		struct edns_data edns;
		edns.edns_present = 1;
		edns.ext_rcode = 0;
		edns.edns_version = EDNS_ADVERTISED_VERSION;
		edns.opt_list = sq->opt_list;
		if(sq->status == serviced_query_UDP_EDNS_FRAG) {
			if(addr_is_ip6(&sq->addr, sq->addrlen)) {
				if(EDNS_FRAG_SIZE_IP6 < EDNS_ADVERTISED_SIZE)
					edns.udp_size = EDNS_FRAG_SIZE_IP6;
				else	edns.udp_size = EDNS_ADVERTISED_SIZE;
			} else {
				if(EDNS_FRAG_SIZE_IP4 < EDNS_ADVERTISED_SIZE)
					edns.udp_size = EDNS_FRAG_SIZE_IP4;
				else	edns.udp_size = EDNS_ADVERTISED_SIZE;
			}
		} else {
			edns.udp_size = EDNS_ADVERTISED_SIZE;
		}
		edns.bits = 0;
		if(sq->dnssec & EDNS_DO)
			edns.bits = EDNS_DO;
		if(sq->dnssec & BIT_CD)
			LDNS_CD_SET(sldns_buffer_begin(buff));
		attach_edns_record(buff, &edns);
	}
}