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
typedef  int /*<<< orphan*/  uint16_t ;
struct query_info {int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct auth_xfer {int /*<<< orphan*/  dclass; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  qinfo ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  memset (struct query_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qinfo_query_encode (int /*<<< orphan*/ *,struct query_info*) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfr_create_soa_probe_packet(struct auth_xfer* xfr, sldns_buffer* buf, 
	uint16_t id)
{
	struct query_info qinfo;

	memset(&qinfo, 0, sizeof(qinfo));
	qinfo.qname = xfr->name;
	qinfo.qname_len = xfr->namelen;
	qinfo.qtype = LDNS_RR_TYPE_SOA;
	qinfo.qclass = xfr->dclass;
	qinfo_query_encode(buf, &qinfo);
	sldns_buffer_write_u16_at(buf, 0, id);
}