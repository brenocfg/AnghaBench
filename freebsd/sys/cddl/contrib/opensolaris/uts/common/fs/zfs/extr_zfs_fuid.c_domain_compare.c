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
struct TYPE_4__ {TYPE_1__* f_ksid; } ;
typedef  TYPE_2__ fuid_domain_t ;
struct TYPE_3__ {int /*<<< orphan*/  kd_name; } ;

/* Variables and functions */
 int AVL_ISIGN (int) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
domain_compare(const void *arg1, const void *arg2)
{
	const fuid_domain_t *node1 = (const fuid_domain_t *)arg1;
	const fuid_domain_t *node2 = (const fuid_domain_t *)arg2;
	int val;

	val = strcmp(node1->f_ksid->kd_name, node2->f_ksid->kd_name);

	return (AVL_ISIGN(val));
}