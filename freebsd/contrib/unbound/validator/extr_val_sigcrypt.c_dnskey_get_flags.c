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
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrset_get_rdata (struct ub_packed_rrset_key*,size_t,int /*<<< orphan*/ **,size_t*) ; 

uint16_t
dnskey_get_flags(struct ub_packed_rrset_key* k, size_t idx)
{
	uint8_t* rdata;
	size_t len;
	uint16_t f;
	rrset_get_rdata(k, idx, &rdata, &len);
	if(len < 2+2)
		return 0;
	memmove(&f, rdata+2, 2);
	f = ntohs(f);
	return f;
}