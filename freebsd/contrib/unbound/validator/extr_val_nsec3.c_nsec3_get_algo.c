#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct packed_rrset_data {int* rr_len; scalar_t__** rr_data; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nsec3_get_algo(struct ub_packed_rrset_key* rrset, int r)
{
        struct packed_rrset_data* d = (struct packed_rrset_data*)
	        rrset->entry.data;
	log_assert(d && r < (int)d->count);
	if(d->rr_len[r] < 2+1)
		return 0; /* malformed */
	return (int)(d->rr_data[r][2+0]);
}