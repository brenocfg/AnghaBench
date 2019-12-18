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
typedef  scalar_t__ time_t ;
struct packed_rrset_data {size_t count; size_t rrsig_count; int /*<<< orphan*/ * rr_ttl; int /*<<< orphan*/  ttl; } ;

/* Variables and functions */

void 
packed_rrset_ttl_add(struct packed_rrset_data* data, time_t add)
{
	size_t i;
	size_t total = data->count + data->rrsig_count;
	data->ttl += add;
	for(i=0; i<total; i++)
		data->rr_ttl[i] += add;
}