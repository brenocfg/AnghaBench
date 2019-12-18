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
struct packed_rrset_data {size_t count; } ;
struct TYPE_2__ {scalar_t__ data; } ;
struct key_entry_key {TYPE_1__ entry; } ;
struct key_entry_data {struct packed_rrset_data* rrset_data; } ;

/* Variables and functions */
 int DNSKEY_BIT_ZSK ; 
 size_t dnskey_get_keysize (struct packed_rrset_data*,size_t) ; 
 int kd_get_flags (struct packed_rrset_data*,size_t) ; 
 int /*<<< orphan*/  key_entry_isgood (struct key_entry_key*) ; 

size_t 
key_entry_keysize(struct key_entry_key* kkey)
{
	struct packed_rrset_data* d;
	/* compute size of smallest ZSK key in the rrset */
	size_t i;
	size_t bits = 0;
	if(!key_entry_isgood(kkey))
		return 0;
	d = ((struct key_entry_data*)kkey->entry.data)->rrset_data;
	for(i=0; i<d->count; i++) {
		if(!(kd_get_flags(d, i) & DNSKEY_BIT_ZSK))
			continue;
		if(i==0 || dnskey_get_keysize(d, i) < bits)
			bits = dnskey_get_keysize(d, i);
	}
	return bits;
}