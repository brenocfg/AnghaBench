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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct packed_rrset_data {size_t count; int* rr_len; int /*<<< orphan*/ ** rr_data; scalar_t__* rr_ttl; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_RRSIG ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_calc_keytag_raw (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sldns_str_print (char**,size_t*,char*,...) ; 
 scalar_t__ sldns_wire2str_class_print (char**,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_wire2str_dname_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_wire2str_rdata_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_wire2str_type_print (char**,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
auth_rr_to_string(uint8_t* nm, size_t nmlen, uint16_t tp, uint16_t cl,
	struct packed_rrset_data* data, size_t i, char* s, size_t buflen)
{
	int w = 0;
	size_t slen = buflen, datlen;
	uint8_t* dat;
	if(i >= data->count) tp = LDNS_RR_TYPE_RRSIG;
	dat = nm;
	datlen = nmlen;
	w += sldns_wire2str_dname_scan(&dat, &datlen, &s, &slen, NULL, 0);
	w += sldns_str_print(&s, &slen, "\t");
	w += sldns_str_print(&s, &slen, "%lu\t", (unsigned long)data->rr_ttl[i]);
	w += sldns_wire2str_class_print(&s, &slen, cl);
	w += sldns_str_print(&s, &slen, "\t");
	w += sldns_wire2str_type_print(&s, &slen, tp);
	w += sldns_str_print(&s, &slen, "\t");
	datlen = data->rr_len[i]-2;
	dat = data->rr_data[i]+2;
	w += sldns_wire2str_rdata_scan(&dat, &datlen, &s, &slen, tp, NULL, 0);

	if(tp == LDNS_RR_TYPE_DNSKEY) {
		w += sldns_str_print(&s, &slen, " ;{id = %u}",
			sldns_calc_keytag_raw(data->rr_data[i]+2,
				data->rr_len[i]-2));
	}
	w += sldns_str_print(&s, &slen, "\n");

	if(w > (int)buflen) {
		log_nametypeclass(0, "RR too long to print", nm, tp, cl);
		return 0;
	}
	return 1;
}