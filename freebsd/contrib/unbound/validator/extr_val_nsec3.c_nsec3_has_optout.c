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
struct packed_rrset_data {int* rr_len; int** rr_data; scalar_t__ count; } ;

/* Variables and functions */
 int NSEC3_OPTOUT ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 

int
nsec3_has_optout(struct ub_packed_rrset_key* rrset, int r)
{
        struct packed_rrset_data* d = (struct packed_rrset_data*)
	        rrset->entry.data;
	log_assert(d && r < (int)d->count);
	if(d->rr_len[r] < 2+2)
		return 0; /* malformed */
	return (int)(d->rr_data[r][2+1] & NSEC3_OPTOUT);
}