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
typedef  size_t uint16_t ;
struct ub_server_stats {int /*<<< orphan*/  qEDNS_DO; int /*<<< orphan*/  qEDNS; int /*<<< orphan*/  qbit_CD; int /*<<< orphan*/  qbit_AD; int /*<<< orphan*/  qbit_Z; int /*<<< orphan*/  qbit_RA; int /*<<< orphan*/  qbit_RD; int /*<<< orphan*/  qbit_TC; int /*<<< orphan*/  qbit_AA; int /*<<< orphan*/  qbit_QR; int /*<<< orphan*/  qipv6; int /*<<< orphan*/  qtls_resume; int /*<<< orphan*/  qtls; int /*<<< orphan*/  qtcp; int /*<<< orphan*/ * qopcode; int /*<<< orphan*/  qclass_big; int /*<<< orphan*/ * qclass; int /*<<< orphan*/  qtype_big; int /*<<< orphan*/ * qtype; } ;
struct edns_data {int bits; scalar_t__ edns_present; } ;
struct comm_reply {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct comm_point {scalar_t__ type; int /*<<< orphan*/ * ssl; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 size_t BIT_AA ; 
 size_t BIT_AD ; 
 size_t BIT_CD ; 
 size_t BIT_QR ; 
 size_t BIT_RA ; 
 size_t BIT_RD ; 
 size_t BIT_TC ; 
 size_t BIT_Z ; 
 int EDNS_DO ; 
 size_t LDNS_OPCODE_WIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ SSL_session_reused (int /*<<< orphan*/ *) ; 
 size_t UB_STATS_QCLASS_NUM ; 
 size_t UB_STATS_QTYPE_NUM ; 
 scalar_t__ addr_is_ip6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ comm_udp ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ ) ; 
 size_t sldns_buffer_read_u16_at (int /*<<< orphan*/ ,int) ; 

void server_stats_insquery(struct ub_server_stats* stats, struct comm_point* c,
	uint16_t qtype, uint16_t qclass, struct edns_data* edns,
	struct comm_reply* repinfo)
{
	uint16_t flags = sldns_buffer_read_u16_at(c->buffer, 2);
	if(qtype < UB_STATS_QTYPE_NUM)
		stats->qtype[qtype]++;
	else	stats->qtype_big++;
	if(qclass < UB_STATS_QCLASS_NUM)
		stats->qclass[qclass]++;
	else	stats->qclass_big++;
	stats->qopcode[ LDNS_OPCODE_WIRE(sldns_buffer_begin(c->buffer)) ]++;
	if(c->type != comm_udp) {
		stats->qtcp++;
		if(c->ssl != NULL) {
			stats->qtls++;
#ifdef HAVE_SSL
			if(SSL_session_reused(c->ssl)) 
				stats->qtls_resume++;
#endif
		}
	}
	if(repinfo && addr_is_ip6(&repinfo->addr, repinfo->addrlen))
		stats->qipv6++;
	if( (flags&BIT_QR) )
		stats->qbit_QR++;
	if( (flags&BIT_AA) )
		stats->qbit_AA++;
	if( (flags&BIT_TC) )
		stats->qbit_TC++;
	if( (flags&BIT_RD) )
		stats->qbit_RD++;
	if( (flags&BIT_RA) )
		stats->qbit_RA++;
	if( (flags&BIT_Z) )
		stats->qbit_Z++;
	if( (flags&BIT_AD) )
		stats->qbit_AD++;
	if( (flags&BIT_CD) )
		stats->qbit_CD++;
	if(edns->edns_present) {
		stats->qEDNS++;
		if( (edns->bits & EDNS_DO) )
			stats->qEDNS_DO++;
	}
}