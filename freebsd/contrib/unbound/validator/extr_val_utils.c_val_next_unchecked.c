#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct reply_info {size_t rrset_count; TYPE_2__** rrsets; } ;
struct packed_rrset_data {scalar_t__ security; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__ entry; } ;

/* Variables and functions */
 scalar_t__ sec_status_unchecked ; 

size_t 
val_next_unchecked(struct reply_info* rep, size_t skip)
{
	size_t i;
	struct packed_rrset_data* d;
	for(i=skip+1; i<rep->rrset_count; i++) {
		d = (struct packed_rrset_data*)rep->rrsets[i]->entry.data;
		if(d->security == sec_status_unchecked) {
			return i;
		}
	}
	return rep->rrset_count;
}