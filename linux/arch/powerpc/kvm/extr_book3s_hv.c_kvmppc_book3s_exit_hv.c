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

/* Variables and functions */
 int /*<<< orphan*/  kvmhv_nested_exit () ; 
 int /*<<< orphan*/  kvmppc_free_host_rm_ops () ; 
 int /*<<< orphan*/ * kvmppc_hv_ops ; 
 int /*<<< orphan*/  kvmppc_radix_exit () ; 
 scalar_t__ kvmppc_radix_possible () ; 

__attribute__((used)) static void kvmppc_book3s_exit_hv(void)
{
	kvmppc_free_host_rm_ops();
	if (kvmppc_radix_possible())
		kvmppc_radix_exit();
	kvmppc_hv_ops = NULL;
	kvmhv_nested_exit();
}