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
struct TYPE_3__ {void* data; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct trust_anchor {TYPE_2__* autr; void* numDNSKEY; void* numDS; struct ub_packed_rrset_key* dnskey_rrset; struct ub_packed_rrset_key* ds_rrset; } ;
struct TYPE_4__ {int /*<<< orphan*/  keys; } ;

/* Variables and functions */
 void* assemble_iterate_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assemble_iterate_dnskey ; 
 int /*<<< orphan*/  assemble_iterate_ds ; 
 scalar_t__ assemble_iterate_hasfirst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autr_rrset_delete (struct ub_packed_rrset_key*) ; 
 void* packed_rrset_heap_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ub_packed_rrset_key* ub_packed_rrset_heap_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
autr_assemble(struct trust_anchor* tp)
{
	struct ub_packed_rrset_key* ubds=NULL, *ubdnskey=NULL;

	/* make packed rrset keys - malloced with no ID number, they
	 * are not in the cache */
	/* make packed rrset data (if there is a key) */
	if(assemble_iterate_hasfirst(assemble_iterate_ds, tp->autr->keys)) {
		ubds = ub_packed_rrset_heap_key(
			assemble_iterate_ds, tp->autr->keys);
		if(!ubds)
			goto error_cleanup;
		ubds->entry.data = packed_rrset_heap_data(
			assemble_iterate_ds, tp->autr->keys);
		if(!ubds->entry.data)
			goto error_cleanup;
	}

	/* make packed DNSKEY data */
	if(assemble_iterate_hasfirst(assemble_iterate_dnskey, tp->autr->keys)) {
		ubdnskey = ub_packed_rrset_heap_key(
			assemble_iterate_dnskey, tp->autr->keys);
		if(!ubdnskey)
			goto error_cleanup;
		ubdnskey->entry.data = packed_rrset_heap_data(
			assemble_iterate_dnskey, tp->autr->keys);
		if(!ubdnskey->entry.data) {
		error_cleanup:
			autr_rrset_delete(ubds);
			autr_rrset_delete(ubdnskey);
			return 0;
		}
	}

	/* we have prepared the new keys so nothing can go wrong any more.
	 * And we are sure we cannot be left without trustanchor after
	 * any errors. Put in the new keys and remove old ones. */

	/* free the old data */
	autr_rrset_delete(tp->ds_rrset);
	autr_rrset_delete(tp->dnskey_rrset);

	/* assign the data to replace the old */
	tp->ds_rrset = ubds;
	tp->dnskey_rrset = ubdnskey;
	tp->numDS = assemble_iterate_count(assemble_iterate_ds,
		tp->autr->keys);
	tp->numDNSKEY = assemble_iterate_count(assemble_iterate_dnskey,
		tp->autr->keys);
	return 1;
}