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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct packed_rrset_data {int* rr_len; scalar_t__** rr_data; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nsec3_get_salt(struct ub_packed_rrset_key* rrset, int r,
	uint8_t** salt, size_t* saltlen)
{
        struct packed_rrset_data* d = (struct packed_rrset_data*)
	        rrset->entry.data;
	log_assert(d && r < (int)d->count);
	if(d->rr_len[r] < 2+5) {
		*salt = 0;
		*saltlen = 0;
		return 0; /* malformed */
	}
	*saltlen = (size_t)d->rr_data[r][2+4];
	if(d->rr_len[r] < 2+5+(size_t)*saltlen) {
		*salt = 0;
		*saltlen = 0;
		return 0; /* malformed */
	}
	*salt = d->rr_data[r]+2+5;
	return 1;
}