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
struct packed_rrset_data {size_t count; size_t* rr_len; int /*<<< orphan*/ * rr_data; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
az_rrset_find_rr(struct packed_rrset_data* d, uint8_t* rdata, size_t len,
	size_t* index)
{
	size_t i;
	for(i=0; i<d->count; i++) {
		if(d->rr_len[i] != len)
			continue;
		if(memcmp(d->rr_data[i], rdata, len) == 0) {
			*index = i;
			return 1;
		}
	}
	return 0;
}