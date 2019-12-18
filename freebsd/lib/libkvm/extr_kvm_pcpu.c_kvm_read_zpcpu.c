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
typedef  scalar_t__ u_long ;
struct pcpu {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_native (int /*<<< orphan*/ *) ; 
 int kvm_read (int /*<<< orphan*/ *,uintptr_t,void*,size_t) ; 

ssize_t
kvm_read_zpcpu(kvm_t *kd, u_long base, void *buf, size_t size, int cpu)
{

	if (!kvm_native(kd))
		return (-1);
	return (kvm_read(kd, (uintptr_t)(base + sizeof(struct pcpu) * cpu),
	    buf, size));
}