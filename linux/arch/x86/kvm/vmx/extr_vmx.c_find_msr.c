#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmx_msrs {unsigned int nr; TYPE_1__* val; } ;
struct TYPE_2__ {unsigned int index; } ;

/* Variables and functions */
 int ENOENT ; 

__attribute__((used)) static int find_msr(struct vmx_msrs *m, unsigned int msr)
{
	unsigned int i;

	for (i = 0; i < m->nr; ++i) {
		if (m->val[i].index == msr)
			return i;
	}
	return -ENOENT;
}