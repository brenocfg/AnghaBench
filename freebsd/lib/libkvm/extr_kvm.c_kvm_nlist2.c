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
struct kvm_nlist {int dummy; } ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 int _kvm_nlist (int /*<<< orphan*/ *,struct kvm_nlist*,int) ; 

int
kvm_nlist2(kvm_t *kd, struct kvm_nlist *nl)
{

	/*
	 * If called via the public interface, permit initialization of
	 * further virtualized modules on demand.
	 */
	return (_kvm_nlist(kd, nl, 1));
}