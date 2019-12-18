#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  size_t uint32_t ;
struct TYPE_4__ {size_t* pt2_wirecount; } ;
struct TYPE_5__ {TYPE_1__ md; } ;

/* Variables and functions */
 size_t PT2PG_MASK ; 

__attribute__((used)) static __inline uint32_t
pt2_wirecount_get(vm_page_t m, uint32_t pte1_idx)
{

	return (m->md.pt2_wirecount[pte1_idx & PT2PG_MASK]);
}