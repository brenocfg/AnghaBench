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
ds_get_keytag(struct ub_packed_rrset_key* ds_rrset, size_t ds_idx)
{
	uint16_t t;
	uint8_t* rdata;
	size_t len;
	rrset_get_rdata(ds_rrset, ds_idx, &rdata, &len);
	if(len < 2+2)
		return 0;
	memmove(&t, rdata+2, 2);
	return ntohs(t);
}