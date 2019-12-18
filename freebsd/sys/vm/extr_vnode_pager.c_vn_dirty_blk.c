#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int vm_page_bits_t ;
typedef  scalar_t__ vm_ooffset_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_3__ {int dirty; scalar_t__ pindex; } ;

/* Variables and functions */
 scalar_t__ IDX_TO_OFF (scalar_t__) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int vn_off2bidx (scalar_t__) ; 

__attribute__((used)) static bool
vn_dirty_blk(vm_page_t m, vm_ooffset_t offset)
{

	KASSERT(IDX_TO_OFF(m->pindex) <= offset &&
	    offset < IDX_TO_OFF(m->pindex + 1),
	    ("page %p pidx %ju offset %ju", m, (uintmax_t)m->pindex,
	    (uintmax_t)offset));
	return ((m->dirty & ((vm_page_bits_t)1 << vn_off2bidx(offset))) != 0);
}