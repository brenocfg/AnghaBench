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
struct TYPE_6__ {struct packed_rrset_data* data; struct ub_packed_rrset_key* key; } ;
struct TYPE_5__ {void* rrset_class; void* type; int /*<<< orphan*/  dname_len; void* dname; } ;
struct ub_packed_rrset_key {TYPE_3__ entry; TYPE_2__ rk; } ;
struct regional {int dummy; } ;
struct packed_rrset_data {int dummy; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct key_entry_key {int /*<<< orphan*/  key_class; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; TYPE_1__ entry; } ;
struct key_entry_data {int /*<<< orphan*/  rrset_data; int /*<<< orphan*/  rrset_type; } ;

/* Variables and functions */
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ub_packed_rrset_key*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  packed_rrset_ptr_fixup (struct packed_rrset_data*) ; 
 int /*<<< orphan*/  packed_rrset_sizeof (int /*<<< orphan*/ ) ; 
 struct ub_packed_rrset_key* regional_alloc (struct regional*,int) ; 
 void* regional_alloc_init (struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ub_packed_rrset_key* 
key_entry_get_rrset(struct key_entry_key* kkey, struct regional* region)
{
	struct key_entry_data* d = (struct key_entry_data*)kkey->entry.data;
	struct ub_packed_rrset_key* rrk;
	struct packed_rrset_data* rrd;
	if(!d || !d->rrset_data)
		return NULL;
	rrk = regional_alloc(region, sizeof(*rrk));
	if(!rrk)
		return NULL;
	memset(rrk, 0, sizeof(*rrk));
	rrk->rk.dname = regional_alloc_init(region, kkey->name, kkey->namelen);
	if(!rrk->rk.dname)
		return NULL;
	rrk->rk.dname_len = kkey->namelen;
	rrk->rk.type = htons(d->rrset_type);
	rrk->rk.rrset_class = htons(kkey->key_class);
	rrk->entry.key = rrk;
	rrd = regional_alloc_init(region, d->rrset_data, 
		packed_rrset_sizeof(d->rrset_data));
	if(!rrd)
		return NULL;
	rrk->entry.data = rrd;
	packed_rrset_ptr_fixup(rrd);
	return rrk;
}