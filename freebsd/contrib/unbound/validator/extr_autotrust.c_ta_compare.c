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
typedef  scalar_t__ uint16_t ;
struct autr_ta {int /*<<< orphan*/  dname_len; int /*<<< orphan*/  rr_len; int /*<<< orphan*/  rr; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_DNSKEY ; 
 scalar_t__ LDNS_RR_TYPE_DS ; 
 int dnskey_compare_skip_revbit (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_wirerr_get_rdata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t sldns_wirerr_get_rdatalen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_wirerr_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ta_compare(struct autr_ta* a, uint16_t t, uint8_t* b, size_t b_len)
{
	if(!a) return -1;
	else if(!b) return -1;
	else if(sldns_wirerr_get_type(a->rr, a->rr_len, a->dname_len) != t)
		return (int)sldns_wirerr_get_type(a->rr, a->rr_len,
			a->dname_len) - (int)t;
	else if(t == LDNS_RR_TYPE_DNSKEY) {
		return dnskey_compare_skip_revbit(
			sldns_wirerr_get_rdata(a->rr, a->rr_len, a->dname_len),
			sldns_wirerr_get_rdatalen(a->rr, a->rr_len,
			a->dname_len), b, b_len);
	}
	else if(t == LDNS_RR_TYPE_DS) {
		if(sldns_wirerr_get_rdatalen(a->rr, a->rr_len, a->dname_len) !=
			b_len)
			return -1;
		return memcmp(sldns_wirerr_get_rdata(a->rr,
			a->rr_len, a->dname_len), b, b_len);
	}
	return -1;
}