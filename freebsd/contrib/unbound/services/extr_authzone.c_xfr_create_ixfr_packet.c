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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct query_info {scalar_t__ qtype; int qclass; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct auth_xfer {int have_zone; int dclass; TYPE_1__* task_transfer; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  serial; } ;
struct auth_master {int /*<<< orphan*/  ixfr; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  qinfo ;
struct TYPE_2__ {int on_ixfr; scalar_t__ ixfr_fail; scalar_t__ on_ixfr_is_axfr; scalar_t__ incoming_xfr_serial; scalar_t__ rr_scan_num; scalar_t__ got_xfr_serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_NSCOUNT_OFF ; 
 scalar_t__ LDNS_RR_TYPE_AXFR ; 
 scalar_t__ LDNS_RR_TYPE_IXFR ; 
 int LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  memset (struct query_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qinfo_query_encode (int /*<<< orphan*/ *,struct query_info*) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sldns_buffer_write_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_write_u8 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
xfr_create_ixfr_packet(struct auth_xfer* xfr, sldns_buffer* buf, uint16_t id,
	struct auth_master* master)
{
	struct query_info qinfo;
	uint32_t serial;
	int have_zone;
	have_zone = xfr->have_zone;
	serial = xfr->serial;

	memset(&qinfo, 0, sizeof(qinfo));
	qinfo.qname = xfr->name;
	qinfo.qname_len = xfr->namelen;
	xfr->task_transfer->got_xfr_serial = 0;
	xfr->task_transfer->rr_scan_num = 0;
	xfr->task_transfer->incoming_xfr_serial = 0;
	xfr->task_transfer->on_ixfr_is_axfr = 0;
	xfr->task_transfer->on_ixfr = 1;
	qinfo.qtype = LDNS_RR_TYPE_IXFR;
	if(!have_zone || xfr->task_transfer->ixfr_fail || !master->ixfr) {
		qinfo.qtype = LDNS_RR_TYPE_AXFR;
		xfr->task_transfer->ixfr_fail = 0;
		xfr->task_transfer->on_ixfr = 0;
	}

	qinfo.qclass = xfr->dclass;
	qinfo_query_encode(buf, &qinfo);
	sldns_buffer_write_u16_at(buf, 0, id);

	/* append serial for IXFR */
	if(qinfo.qtype == LDNS_RR_TYPE_IXFR) {
		size_t end = sldns_buffer_limit(buf);
		sldns_buffer_clear(buf);
		sldns_buffer_set_position(buf, end);
		/* auth section count 1 */
		sldns_buffer_write_u16_at(buf, LDNS_NSCOUNT_OFF, 1);
		/* write SOA */
		sldns_buffer_write_u8(buf, 0xC0); /* compressed ptr to qname */
		sldns_buffer_write_u8(buf, 0x0C);
		sldns_buffer_write_u16(buf, LDNS_RR_TYPE_SOA);
		sldns_buffer_write_u16(buf, qinfo.qclass);
		sldns_buffer_write_u32(buf, 0); /* ttl */
		sldns_buffer_write_u16(buf, 22); /* rdata length */
		sldns_buffer_write_u8(buf, 0); /* . */
		sldns_buffer_write_u8(buf, 0); /* . */
		sldns_buffer_write_u32(buf, serial); /* serial */
		sldns_buffer_write_u32(buf, 0); /* refresh */
		sldns_buffer_write_u32(buf, 0); /* retry */
		sldns_buffer_write_u32(buf, 0); /* expire */
		sldns_buffer_write_u32(buf, 0); /* minimum */
		sldns_buffer_flip(buf);
	}
}