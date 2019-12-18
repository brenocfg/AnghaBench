#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct trust_anchor {scalar_t__ numDS; scalar_t__ numDNSKEY; TYPE_4__* dnskey_rrset; TYPE_3__* ds_rrset; } ;
struct packed_rrset_data {size_t count; } ;
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_8__ {TYPE_2__ entry; } ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_7__ {TYPE_1__ entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  dnskey_calc_keytag (TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  ds_get_keytag (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  keytag_compare ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 

size_t
anchor_list_keytags(struct trust_anchor* ta, uint16_t* list, size_t num)
{
	size_t i, ret = 0;
	if(ta->numDS == 0 && ta->numDNSKEY == 0)
		return 0; /* insecure point */
	if(ta->numDS != 0 && ta->ds_rrset) {
		struct packed_rrset_data* d=(struct packed_rrset_data*)
			ta->ds_rrset->entry.data;
		for(i=0; i<d->count; i++) {
			if(ret == num) continue;
			list[ret++] = ds_get_keytag(ta->ds_rrset, i);
		}
	}
	if(ta->numDNSKEY != 0 && ta->dnskey_rrset) {
		struct packed_rrset_data* d=(struct packed_rrset_data*)
			ta->dnskey_rrset->entry.data;
		for(i=0; i<d->count; i++) {
			if(ret == num) continue;
			list[ret++] = dnskey_calc_keytag(ta->dnskey_rrset, i);
		}
	}
	qsort(list, ret, sizeof(*list), keytag_compare);
	return ret;
}