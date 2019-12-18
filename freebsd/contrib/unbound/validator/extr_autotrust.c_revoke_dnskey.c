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
typedef  int uint16_t ;
struct autr_ta {int /*<<< orphan*/  dname_len; int /*<<< orphan*/  rr_len; int /*<<< orphan*/  rr; } ;

/* Variables and functions */
 int LDNS_KEY_REVOKE_KEY ; 
 scalar_t__ LDNS_RR_TYPE_DNSKEY ; 
 int sldns_read_uint16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sldns_wirerr_get_rdata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sldns_wirerr_get_rdatalen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_wirerr_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_write_uint16 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
revoke_dnskey(struct autr_ta* ta, int off)
{
	uint16_t flags;
	uint8_t* data;
	if(sldns_wirerr_get_type(ta->rr, ta->rr_len, ta->dname_len) !=
		LDNS_RR_TYPE_DNSKEY)
		return;
	if(sldns_wirerr_get_rdatalen(ta->rr, ta->rr_len, ta->dname_len) < 2)
		return;
	data = sldns_wirerr_get_rdata(ta->rr, ta->rr_len, ta->dname_len);
	flags = sldns_read_uint16(data);
	if (off && (flags&LDNS_KEY_REVOKE_KEY))
		flags ^= LDNS_KEY_REVOKE_KEY; /* flip */
	else
		flags |= LDNS_KEY_REVOKE_KEY;
	sldns_write_uint16(data, flags);
}