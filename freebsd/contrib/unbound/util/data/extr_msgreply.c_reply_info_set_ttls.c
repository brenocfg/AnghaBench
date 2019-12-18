#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct reply_info {size_t rrset_count; TYPE_3__* ref; int /*<<< orphan*/  serve_expired_ttl; int /*<<< orphan*/  prefetch_ttl; int /*<<< orphan*/  ttl; } ;
struct packed_rrset_data {size_t count; size_t rrsig_count; int /*<<< orphan*/ * rr_ttl; int /*<<< orphan*/  ttl; } ;
struct TYPE_6__ {TYPE_2__* key; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_5__ {TYPE_1__ entry; } ;

/* Variables and functions */

void 
reply_info_set_ttls(struct reply_info* rep, time_t timenow)
{
	size_t i, j;
	rep->ttl += timenow;
	rep->prefetch_ttl += timenow;
	rep->serve_expired_ttl += timenow;
	for(i=0; i<rep->rrset_count; i++) {
		struct packed_rrset_data* data = (struct packed_rrset_data*)
			rep->ref[i].key->entry.data;
		if(i>0 && rep->ref[i].key == rep->ref[i-1].key)
			continue;
		data->ttl += timenow;
		for(j=0; j<data->count + data->rrsig_count; j++) {
			data->rr_ttl[j] += timenow;
		}
	}
}