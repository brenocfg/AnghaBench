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
struct ub_packed_rrset_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rrset_get_rdata (struct ub_packed_rrset_key*,size_t,int /*<<< orphan*/ **,size_t*) ; 

__attribute__((used)) static void
ds_get_sigdata(struct ub_packed_rrset_key* k, size_t idx, uint8_t** digest,
        size_t* len)
{
	uint8_t* rdata;
	size_t rdlen;
	rrset_get_rdata(k, idx, &rdata, &rdlen);
	if(rdlen < 2+5) {
		*digest = NULL;
		*len = 0;
		return;
	}
	*digest = rdata + 2 + 4;
	*len = rdlen - 2 - 4;
}