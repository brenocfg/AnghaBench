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
typedef  size_t u_long ;
typedef  scalar_t__ off_t ;
struct TYPE_3__ {scalar_t__ pt_sparse_off; scalar_t__ page_map; } ;
typedef  TYPE_1__ kvm_t ;

/* Variables and functions */

void *
_kvm_pmap_get(kvm_t *kd, u_long idx, size_t len)
{
	uintptr_t off = idx * len;

	if ((off_t)off >= kd->pt_sparse_off)
		return (NULL);
	return (void *)((uintptr_t)kd->page_map + off);
}