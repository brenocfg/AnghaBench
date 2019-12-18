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
struct vm_domainset_iter {int dummy; } ;
struct domainset {int dummy; } ;

/* Variables and functions */

void
vm_domainset_iter_policy_init(struct vm_domainset_iter *di,
    struct domainset *ds, int *domain, int *flags)
{

	*domain = 0;
}