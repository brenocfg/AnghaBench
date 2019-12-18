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
struct packed_rrset_data {int* rr_len; int /*<<< orphan*/ ** rr_data; } ;

/* Variables and functions */

__attribute__((used)) static uint8_t
rrsig_get_labcount(struct packed_rrset_data* d, size_t sig)
{
	if(d->rr_len[sig] < 2+4)
		return 0; /* bad sig length */
	return d->rr_data[sig][2+3];
}