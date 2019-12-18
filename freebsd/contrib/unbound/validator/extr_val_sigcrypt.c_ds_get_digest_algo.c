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
typedef  scalar_t__ uint8_t ;
struct ub_packed_rrset_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rrset_get_rdata (struct ub_packed_rrset_key*,size_t,scalar_t__**,size_t*) ; 

int
ds_get_digest_algo(struct ub_packed_rrset_key* k, size_t idx)
{
	uint8_t* rdata;
	size_t len;
	rrset_get_rdata(k, idx, &rdata, &len);
	if(len < 2+4)
		return 0;
	return (int)rdata[2+3];
}