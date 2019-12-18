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
struct TYPE_2__ {int /*<<< orphan*/  f_idx; } ;
typedef  TYPE_1__ fuid_domain_t ;

/* Variables and functions */
 int AVL_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
idx_compare(const void *arg1, const void *arg2)
{
	const fuid_domain_t *node1 = (const fuid_domain_t *)arg1;
	const fuid_domain_t *node2 = (const fuid_domain_t *)arg2;

	return (AVL_CMP(node1->f_idx, node2->f_idx));
}