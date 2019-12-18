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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct packed_rrset_data {size_t rrsig_count; int* rr_len; size_t count; scalar_t__* rr_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t 
rrset_get_sig_keytag(struct ub_packed_rrset_key* k, size_t sig_idx)
{
	uint16_t t;
	struct packed_rrset_data* d = (struct packed_rrset_data*)k->entry.data;
	log_assert(sig_idx < d->rrsig_count);
	if(d->rr_len[d->count + sig_idx] < 2+18)
		return 0;
	memmove(&t, d->rr_data[d->count + sig_idx]+2+16, 2);
	return ntohs(t);
}