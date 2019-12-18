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
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  _kvm_pcpu_clear () ; 
 scalar_t__ _kvm_pcpu_init (int /*<<< orphan*/ *) ; 
 scalar_t__ maxcpu ; 

int
kvm_getmaxcpu(kvm_t *kd)
{

	if (kd == NULL) {
		_kvm_pcpu_clear();
		return (0);
	}

	if (maxcpu == 0)
		if (_kvm_pcpu_init(kd) < 0)
			return (-1);
	return (maxcpu);
}