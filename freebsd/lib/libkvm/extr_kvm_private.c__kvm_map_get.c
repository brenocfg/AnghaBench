#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int off_t ;
struct TYPE_4__ {int pt_sparse_off; scalar_t__ sparse_map; scalar_t__ page_map; } ;
typedef  TYPE_1__ kvm_t ;

/* Variables and functions */
 int _kvm_pt_find (TYPE_1__*,int /*<<< orphan*/ ,unsigned int) ; 

void *
_kvm_map_get(kvm_t *kd, u_long pa, unsigned int page_size)
{
	off_t off;
	uintptr_t addr;

	off = _kvm_pt_find(kd, pa, page_size);
	if (off == -1)
		return NULL;

	addr = (uintptr_t)kd->page_map + off;
	if (off >= kd->pt_sparse_off)
		addr = (uintptr_t)kd->sparse_map + (off - kd->pt_sparse_off);
	return (void *)addr;
}