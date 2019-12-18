#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xucred {scalar_t__ cr_uid; scalar_t__ cr_ngroups; int /*<<< orphan*/  cr_groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_ARRAYS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
compare_cred(struct xucred *cr0, struct xucred *cr1)
{

	if (cr0->cr_uid != cr1->cr_uid || cr0->cr_ngroups != cr1->cr_ngroups)
		return (1);

	COMPARE_ARRAYS(cr0->cr_groups, cr1->cr_groups, cr0->cr_ngroups);
}