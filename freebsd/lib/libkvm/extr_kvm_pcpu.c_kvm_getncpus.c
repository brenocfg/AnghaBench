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
 scalar_t__ _kvm_pcpu_init (int /*<<< orphan*/ *) ; 
 scalar_t__ mp_ncpus ; 

int
kvm_getncpus(kvm_t *kd)
{

	if (mp_ncpus == 0)
		if (_kvm_pcpu_init(kd) < 0)
			return (-1);
	return (mp_ncpus);
}