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
struct ub_packed_rrset_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rrset_get_rdata (struct ub_packed_rrset_key*,size_t,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  sldns_calc_keytag_raw (int /*<<< orphan*/ *,size_t) ; 

uint16_t 
dnskey_calc_keytag(struct ub_packed_rrset_key* dnskey_rrset, size_t dnskey_idx)
{
	uint8_t* data;
	size_t len;
	rrset_get_rdata(dnskey_rrset, dnskey_idx, &data, &len);
	/* do not pass rdatalen to ldns */
	return sldns_calc_keytag_raw(data+2, len-2);
}