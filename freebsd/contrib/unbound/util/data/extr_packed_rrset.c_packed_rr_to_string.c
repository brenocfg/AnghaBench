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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ time_t ;
struct TYPE_4__ {int dname_len; int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  type; int /*<<< orphan*/ * dname; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; TYPE_1__ entry; } ;
struct packed_rrset_data {int* rr_len; size_t count; int /*<<< orphan*/ ** rr_data; scalar_t__* rr_ttl; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_RRSIG ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_info (char*,int,char*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int sldns_wire2str_rr_buf (int /*<<< orphan*/ *,size_t,char*,size_t) ; 
 int /*<<< orphan*/  sldns_write_uint16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_write_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int packed_rr_to_string(struct ub_packed_rrset_key* rrset, size_t i,
	time_t now, char* dest, size_t dest_len)
{
	struct packed_rrset_data* d = (struct packed_rrset_data*)rrset->
		entry.data;
	uint8_t rr[65535];
	size_t rlen = rrset->rk.dname_len + 2 + 2 + 4 + d->rr_len[i];
	log_assert(dest_len > 0 && dest);
	if(rlen > dest_len) {
		dest[0] = 0;
		return 0;
	}
	memmove(rr, rrset->rk.dname, rrset->rk.dname_len);
	if(i < d->count)
		memmove(rr+rrset->rk.dname_len, &rrset->rk.type, 2);
	else	sldns_write_uint16(rr+rrset->rk.dname_len, LDNS_RR_TYPE_RRSIG);
	memmove(rr+rrset->rk.dname_len+2, &rrset->rk.rrset_class, 2);
	sldns_write_uint32(rr+rrset->rk.dname_len+4,
		(uint32_t)(d->rr_ttl[i]-now));
	memmove(rr+rrset->rk.dname_len+8, d->rr_data[i], d->rr_len[i]);
	if(sldns_wire2str_rr_buf(rr, rlen, dest, dest_len) == -1) {
		log_info("rrbuf failure %d %s", (int)d->rr_len[i], dest);
		dest[0] = 0;
		return 0;
	} 
	return 1;
}