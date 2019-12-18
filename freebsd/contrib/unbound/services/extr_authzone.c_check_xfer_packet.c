#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct auth_xfer {scalar_t__ dclass; TYPE_2__* task_transfer; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  rcode ;
struct TYPE_4__ {scalar_t__ id; int ixfr_fail; int rr_scan_num; int on_ixfr_is_axfr; int got_xfr_serial; scalar_t__ incoming_xfr_serial; TYPE_1__* master; scalar_t__ on_ixfr; } ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int LDNS_ANCOUNT (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_ARCOUNT (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_HEADER_SIZE ; 
 scalar_t__ LDNS_ID_WIRE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_NSCOUNT (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_OPCODE_WIRE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_PACKET_QUERY ; 
 int LDNS_QDCOUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LDNS_QR_WIRE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_RCODE_FORMERR ; 
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RCODE_NOTIMPL ; 
 scalar_t__ LDNS_RCODE_REFUSED ; 
 scalar_t__ LDNS_RCODE_SERVFAIL ; 
 scalar_t__ LDNS_RCODE_WIRE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_RR_TYPE_AXFR ; 
 scalar_t__ LDNS_RR_TYPE_IXFR ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 scalar_t__ LDNS_TC_WIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ dname_pkt_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pkt_dname_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_at (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_position (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_read_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_read_u32 (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_read_u32_at (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_wire2str_rcode_buf (int,char*,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
check_xfer_packet(sldns_buffer* pkt, struct auth_xfer* xfr,
	int* gonextonfail, int* transferdone)
{
	uint8_t* wire = sldns_buffer_begin(pkt);
	int i;
	if(sldns_buffer_limit(pkt) < LDNS_HEADER_SIZE) {
		verbose(VERB_ALGO, "xfr to %s failed, packet too small",
			xfr->task_transfer->master->host);
		return 0;
	}
	if(!LDNS_QR_WIRE(wire)) {
		verbose(VERB_ALGO, "xfr to %s failed, packet has no QR flag",
			xfr->task_transfer->master->host);
		return 0;
	}
	if(LDNS_TC_WIRE(wire)) {
		verbose(VERB_ALGO, "xfr to %s failed, packet has TC flag",
			xfr->task_transfer->master->host);
		return 0;
	}
	/* check ID */
	if(LDNS_ID_WIRE(wire) != xfr->task_transfer->id) {
		verbose(VERB_ALGO, "xfr to %s failed, packet wrong ID",
			xfr->task_transfer->master->host);
		return 0;
	}
	if(LDNS_RCODE_WIRE(wire) != LDNS_RCODE_NOERROR) {
		char rcode[32];
		sldns_wire2str_rcode_buf((int)LDNS_RCODE_WIRE(wire), rcode,
			sizeof(rcode));
		/* if we are doing IXFR, check for fallback */
		if(xfr->task_transfer->on_ixfr) {
			if(LDNS_RCODE_WIRE(wire) == LDNS_RCODE_NOTIMPL ||
				LDNS_RCODE_WIRE(wire) == LDNS_RCODE_SERVFAIL ||
				LDNS_RCODE_WIRE(wire) == LDNS_RCODE_REFUSED ||
				LDNS_RCODE_WIRE(wire) == LDNS_RCODE_FORMERR) {
				verbose(VERB_ALGO, "xfr to %s, fallback "
					"from IXFR to AXFR (with rcode %s)",
					xfr->task_transfer->master->host,
					rcode);
				xfr->task_transfer->ixfr_fail = 1;
				*gonextonfail = 0;
				return 0;
			}
		}
		verbose(VERB_ALGO, "xfr to %s failed, packet with rcode %s",
			xfr->task_transfer->master->host, rcode);
		return 0;
	}
	if(LDNS_OPCODE_WIRE(wire) != LDNS_PACKET_QUERY) {
		verbose(VERB_ALGO, "xfr to %s failed, packet with bad opcode",
			xfr->task_transfer->master->host);
		return 0;
	}
	if(LDNS_QDCOUNT(wire) > 1) {
		verbose(VERB_ALGO, "xfr to %s failed, packet has qdcount %d",
			xfr->task_transfer->master->host,
			(int)LDNS_QDCOUNT(wire));
		return 0;
	}

	/* check qname */
	sldns_buffer_set_position(pkt, LDNS_HEADER_SIZE);
	for(i=0; i<(int)LDNS_QDCOUNT(wire); i++) {
		size_t pos = sldns_buffer_position(pkt);
		uint16_t qtype, qclass;
		if(pkt_dname_len(pkt) == 0) {
			verbose(VERB_ALGO, "xfr to %s failed, packet with "
				"malformed dname",
				xfr->task_transfer->master->host);
			return 0;
		}
		if(dname_pkt_compare(pkt, sldns_buffer_at(pkt, pos),
			xfr->name) != 0) {
			verbose(VERB_ALGO, "xfr to %s failed, packet with "
				"wrong qname",
				xfr->task_transfer->master->host);
			return 0;
		}
		if(sldns_buffer_remaining(pkt) < 4) {
			verbose(VERB_ALGO, "xfr to %s failed, packet with "
				"truncated query RR",
				xfr->task_transfer->master->host);
			return 0;
		}
		qtype = sldns_buffer_read_u16(pkt);
		qclass = sldns_buffer_read_u16(pkt);
		if(qclass != xfr->dclass) {
			verbose(VERB_ALGO, "xfr to %s failed, packet with "
				"wrong qclass",
				xfr->task_transfer->master->host);
			return 0;
		}
		if(xfr->task_transfer->on_ixfr) {
			if(qtype != LDNS_RR_TYPE_IXFR) {
				verbose(VERB_ALGO, "xfr to %s failed, packet "
					"with wrong qtype, expected IXFR",
				xfr->task_transfer->master->host);
				return 0;
			}
		} else {
			if(qtype != LDNS_RR_TYPE_AXFR) {
				verbose(VERB_ALGO, "xfr to %s failed, packet "
					"with wrong qtype, expected AXFR",
				xfr->task_transfer->master->host);
				return 0;
			}
		}
	}

	/* check parse of RRs in packet, store first SOA serial
	 * to be able to detect last SOA (with that serial) to see if done */
	/* also check for IXFR 'zone up to date' reply */
	for(i=0; i<(int)LDNS_ANCOUNT(wire); i++) {
		size_t pos = sldns_buffer_position(pkt);
		uint16_t tp, rdlen;
		if(pkt_dname_len(pkt) == 0) {
			verbose(VERB_ALGO, "xfr to %s failed, packet with "
				"malformed dname in answer section",
				xfr->task_transfer->master->host);
			return 0;
		}
		if(sldns_buffer_remaining(pkt) < 10) {
			verbose(VERB_ALGO, "xfr to %s failed, packet with "
				"truncated RR",
				xfr->task_transfer->master->host);
			return 0;
		}
		tp = sldns_buffer_read_u16(pkt);
		(void)sldns_buffer_read_u16(pkt); /* class */
		(void)sldns_buffer_read_u32(pkt); /* ttl */
		rdlen = sldns_buffer_read_u16(pkt);
		if(sldns_buffer_remaining(pkt) < rdlen) {
			verbose(VERB_ALGO, "xfr to %s failed, packet with "
				"truncated RR rdata",
				xfr->task_transfer->master->host);
			return 0;
		}

		/* RR parses (haven't checked rdata itself), now look at
		 * SOA records to see serial number */
		if(xfr->task_transfer->rr_scan_num == 0 &&
			tp != LDNS_RR_TYPE_SOA) {
			verbose(VERB_ALGO, "xfr to %s failed, packet with "
				"malformed zone transfer, no start SOA",
				xfr->task_transfer->master->host);
			return 0;
		}
		if(xfr->task_transfer->rr_scan_num == 1 &&
			tp != LDNS_RR_TYPE_SOA) {
			/* second RR is not a SOA record, this is not an IXFR
			 * the master is replying with an AXFR */
			xfr->task_transfer->on_ixfr_is_axfr = 1;
		}
		if(tp == LDNS_RR_TYPE_SOA) {
			uint32_t serial;
			if(rdlen < 22) {
				verbose(VERB_ALGO, "xfr to %s failed, packet "
					"with SOA with malformed rdata",
					xfr->task_transfer->master->host);
				return 0;
			}
			if(dname_pkt_compare(pkt, sldns_buffer_at(pkt, pos),
				xfr->name) != 0) {
				verbose(VERB_ALGO, "xfr to %s failed, packet "
					"with SOA with wrong dname",
					xfr->task_transfer->master->host);
				return 0;
			}

			/* read serial number of SOA */
			serial = sldns_buffer_read_u32_at(pkt,
				sldns_buffer_position(pkt)+rdlen-20);

			/* check for IXFR 'zone has SOA x' reply */
			if(xfr->task_transfer->on_ixfr &&
				xfr->task_transfer->rr_scan_num == 0 &&
				LDNS_ANCOUNT(wire)==1) {
				verbose(VERB_ALGO, "xfr to %s ended, "
					"IXFR reply that zone has serial %u",
					xfr->task_transfer->master->host,
					(unsigned)serial);
				return 0;
			}

			/* if first SOA, store serial number */
			if(xfr->task_transfer->got_xfr_serial == 0) {
				xfr->task_transfer->got_xfr_serial = 1;
				xfr->task_transfer->incoming_xfr_serial =
					serial;
				verbose(VERB_ALGO, "xfr %s: contains "
					"SOA serial %u",
					xfr->task_transfer->master->host,
					(unsigned)serial);
			/* see if end of AXFR */
			} else if(!xfr->task_transfer->on_ixfr ||
				xfr->task_transfer->on_ixfr_is_axfr) {
				/* second SOA with serial is the end
				 * for AXFR */
				*transferdone = 1;
				verbose(VERB_ALGO, "xfr %s: last AXFR packet",
					xfr->task_transfer->master->host);
			/* for IXFR, count SOA records with that serial */
			} else if(xfr->task_transfer->incoming_xfr_serial ==
				serial && xfr->task_transfer->got_xfr_serial
				== 1) {
				xfr->task_transfer->got_xfr_serial++;
			/* if not first soa, if serial==firstserial, the
			 * third time we are at the end, for IXFR */
			} else if(xfr->task_transfer->incoming_xfr_serial ==
				serial && xfr->task_transfer->got_xfr_serial
				== 2) {
				verbose(VERB_ALGO, "xfr %s: last IXFR packet",
					xfr->task_transfer->master->host);
				*transferdone = 1;
				/* continue parse check, if that succeeds,
				 * transfer is done */
			}
		}
		xfr->task_transfer->rr_scan_num++;

		/* skip over RR rdata to go to the next RR */
		sldns_buffer_skip(pkt, (ssize_t)rdlen);
	}

	/* check authority section */
	/* we skip over the RRs checking packet format */
	for(i=0; i<(int)LDNS_NSCOUNT(wire); i++) {
		uint16_t rdlen;
		if(pkt_dname_len(pkt) == 0) {
			verbose(VERB_ALGO, "xfr to %s failed, packet with "
				"malformed dname in authority section",
				xfr->task_transfer->master->host);
			return 0;
		}
		if(sldns_buffer_remaining(pkt) < 10) {
			verbose(VERB_ALGO, "xfr to %s failed, packet with "
				"truncated RR",
				xfr->task_transfer->master->host);
			return 0;
		}
		(void)sldns_buffer_read_u16(pkt); /* type */
		(void)sldns_buffer_read_u16(pkt); /* class */
		(void)sldns_buffer_read_u32(pkt); /* ttl */
		rdlen = sldns_buffer_read_u16(pkt);
		if(sldns_buffer_remaining(pkt) < rdlen) {
			verbose(VERB_ALGO, "xfr to %s failed, packet with "
				"truncated RR rdata",
				xfr->task_transfer->master->host);
			return 0;
		}
		/* skip over RR rdata to go to the next RR */
		sldns_buffer_skip(pkt, (ssize_t)rdlen);
	}

	/* check additional section */
	for(i=0; i<(int)LDNS_ARCOUNT(wire); i++) {
		uint16_t rdlen;
		if(pkt_dname_len(pkt) == 0) {
			verbose(VERB_ALGO, "xfr to %s failed, packet with "
				"malformed dname in additional section",
				xfr->task_transfer->master->host);
			return 0;
		}
		if(sldns_buffer_remaining(pkt) < 10) {
			verbose(VERB_ALGO, "xfr to %s failed, packet with "
				"truncated RR",
				xfr->task_transfer->master->host);
			return 0;
		}
		(void)sldns_buffer_read_u16(pkt); /* type */
		(void)sldns_buffer_read_u16(pkt); /* class */
		(void)sldns_buffer_read_u32(pkt); /* ttl */
		rdlen = sldns_buffer_read_u16(pkt);
		if(sldns_buffer_remaining(pkt) < rdlen) {
			verbose(VERB_ALGO, "xfr to %s failed, packet with "
				"truncated RR rdata",
				xfr->task_transfer->master->host);
			return 0;
		}
		/* skip over RR rdata to go to the next RR */
		sldns_buffer_skip(pkt, (ssize_t)rdlen);
	}

	return 1;
}