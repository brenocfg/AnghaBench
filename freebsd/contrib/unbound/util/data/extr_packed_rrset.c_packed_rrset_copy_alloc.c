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
struct packed_rrset_data {int dummy; } ;
typedef  struct packed_rrset_data uint8_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {void* data; int /*<<< orphan*/  hash; } ;
struct TYPE_3__ {struct packed_rrset_data* dname; int /*<<< orphan*/  dname_len; } ;
struct ub_packed_rrset_key {TYPE_2__ entry; TYPE_1__ rk; } ;
struct alloc_cache {int dummy; } ;

/* Variables and functions */
 struct ub_packed_rrset_key* alloc_special_obtain (struct alloc_cache*) ; 
 int /*<<< orphan*/  alloc_special_release (struct alloc_cache*,struct ub_packed_rrset_key*) ; 
 int /*<<< orphan*/  free (struct packed_rrset_data*) ; 
 scalar_t__ memdup (struct packed_rrset_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packed_rrset_ptr_fixup (struct packed_rrset_data*) ; 
 int /*<<< orphan*/  packed_rrset_sizeof (struct packed_rrset_data*) ; 
 int /*<<< orphan*/  packed_rrset_ttl_add (struct packed_rrset_data*,int /*<<< orphan*/ ) ; 

struct ub_packed_rrset_key* 
packed_rrset_copy_alloc(struct ub_packed_rrset_key* key, 
	struct alloc_cache* alloc, time_t now)
{
	struct packed_rrset_data* fd, *dd;
	struct ub_packed_rrset_key* dk = alloc_special_obtain(alloc);
	if(!dk) return NULL;
	fd = (struct packed_rrset_data*)key->entry.data;
	dk->entry.hash = key->entry.hash;
	dk->rk = key->rk;
	dk->rk.dname = (uint8_t*)memdup(key->rk.dname, key->rk.dname_len);
	if(!dk->rk.dname) {
		alloc_special_release(alloc, dk);
		return NULL;
	}
	dd = (struct packed_rrset_data*)memdup(fd, packed_rrset_sizeof(fd));
	if(!dd) {
		free(dk->rk.dname);
		alloc_special_release(alloc, dk);
		return NULL;
	}
	packed_rrset_ptr_fixup(dd);
	dk->entry.data = (void*)dd;
	packed_rrset_ttl_add(dd, now);
	return dk;
}