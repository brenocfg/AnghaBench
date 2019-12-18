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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct packed_rrset_data {size_t count; size_t rrsig_count; size_t* rr_len; int /*<<< orphan*/ ** rr_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rrset_get_rdata(struct ub_packed_rrset_key* k, size_t idx, uint8_t** rdata,
	size_t* len)
{
	struct packed_rrset_data* d = (struct packed_rrset_data*)k->entry.data;
	log_assert(d && idx < (d->count + d->rrsig_count));
	*rdata = d->rr_data[idx];
	*len = d->rr_len[idx];
}