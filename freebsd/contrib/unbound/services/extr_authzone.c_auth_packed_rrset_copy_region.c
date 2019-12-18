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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {void* rrset_class; void* type; int /*<<< orphan*/  dname_len; int /*<<< orphan*/  dname; } ;
struct TYPE_3__ {int /*<<< orphan*/  hash; int /*<<< orphan*/  data; struct ub_packed_rrset_key* key; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; TYPE_1__ entry; } ;
struct regional {int dummy; } ;
struct auth_zone {int /*<<< orphan*/  dclass; } ;
struct auth_rrset {int /*<<< orphan*/  type; int /*<<< orphan*/  data; } ;
struct auth_data {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ub_packed_rrset_key*,int /*<<< orphan*/ ,int) ; 
 struct ub_packed_rrset_key* packed_rrset_copy_region (struct ub_packed_rrset_key*,struct regional*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrset_key_hash (TYPE_2__*) ; 

__attribute__((used)) static struct ub_packed_rrset_key*
auth_packed_rrset_copy_region(struct auth_zone* z, struct auth_data* node,
	struct auth_rrset* rrset, struct regional* region, time_t adjust)
{
	struct ub_packed_rrset_key key;
	memset(&key, 0, sizeof(key));
	key.entry.key = &key;
	key.entry.data = rrset->data;
	key.rk.dname = node->name;
	key.rk.dname_len = node->namelen;
	key.rk.type = htons(rrset->type);
	key.rk.rrset_class = htons(z->dclass);
	key.entry.hash = rrset_key_hash(&key.rk);
	return packed_rrset_copy_region(&key, region, adjust);
}