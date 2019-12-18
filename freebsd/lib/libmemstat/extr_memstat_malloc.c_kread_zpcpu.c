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
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 int MEMSTAT_ERROR_KVM ; 
 int MEMSTAT_ERROR_KVM_SHORTREAD ; 
 scalar_t__ kvm_read_zpcpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t,int) ; 

__attribute__((used)) static int
kread_zpcpu(kvm_t *kvm, u_long base, void *buf, size_t size, int cpu)
{
	ssize_t ret;

	ret = kvm_read_zpcpu(kvm, base, buf, size, cpu);
	if (ret < 0)
		return (MEMSTAT_ERROR_KVM);
	if ((size_t)ret != size)
		return (MEMSTAT_ERROR_KVM_SHORTREAD);
	return (0);
}