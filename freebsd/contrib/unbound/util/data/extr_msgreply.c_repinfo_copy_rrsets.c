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
struct TYPE_4__ {void* data; int /*<<< orphan*/  hash; } ;
struct TYPE_3__ {size_t dname_len; struct packed_rrset_data* dname; } ;
struct ub_packed_rrset_key {TYPE_2__ entry; TYPE_1__ rk; int /*<<< orphan*/  id; } ;
struct reply_info {size_t rrset_count; struct ub_packed_rrset_key** rrsets; } ;
struct regional {int dummy; } ;

/* Variables and functions */
 scalar_t__ memdup (struct packed_rrset_data*,size_t) ; 
 int /*<<< orphan*/  packed_rrset_ptr_fixup (struct packed_rrset_data*) ; 
 size_t packed_rrset_sizeof (struct packed_rrset_data*) ; 
 scalar_t__ regional_alloc_init (struct regional*,struct packed_rrset_data*,size_t) ; 

__attribute__((used)) static int
repinfo_copy_rrsets(struct reply_info* dest, struct reply_info* from, 
	struct regional* region)
{
	size_t i, s;
	struct packed_rrset_data* fd, *dd;
	struct ub_packed_rrset_key* fk, *dk;
	for(i=0; i<dest->rrset_count; i++) {
		fk = from->rrsets[i];
		dk = dest->rrsets[i];
		fd = (struct packed_rrset_data*)fk->entry.data;
		dk->entry.hash = fk->entry.hash;
		dk->rk = fk->rk;
		if(region) {
			dk->id = fk->id;
			dk->rk.dname = (uint8_t*)regional_alloc_init(region,
				fk->rk.dname, fk->rk.dname_len);
		} else	
			dk->rk.dname = (uint8_t*)memdup(fk->rk.dname, 
				fk->rk.dname_len);
		if(!dk->rk.dname)
			return 0;
		s = packed_rrset_sizeof(fd);
		if(region)
			dd = (struct packed_rrset_data*)regional_alloc_init(
				region, fd, s);
		else	dd = (struct packed_rrset_data*)memdup(fd, s);
		if(!dd) 
			return 0;
		packed_rrset_ptr_fixup(dd);
		dk->entry.data = (void*)dd;
	}
	return 1;
}