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
typedef  scalar_t__ u_int ;
struct TYPE_4__ {TYPE_1__* vmd_pagequeues; } ;
struct TYPE_3__ {scalar_t__ pq_cnt; } ;

/* Variables and functions */
 TYPE_2__* vm_dom ; 
 int vm_ndomains ; 

__attribute__((used)) static u_int
vm_pagequeue_count(int pq)
{
	u_int v;
	int i;

	v = 0;
	for (i = 0; i < vm_ndomains; i++)
		v += vm_dom[i].vmd_pagequeues[pq].pq_cnt;

	return (v);
}