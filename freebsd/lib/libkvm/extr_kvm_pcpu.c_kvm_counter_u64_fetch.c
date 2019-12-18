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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  kvm_t ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 scalar_t__ _kvm_pcpu_init (int /*<<< orphan*/ *) ; 
 int kvm_read_zpcpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int,int) ; 
 int mp_ncpus ; 

uint64_t
kvm_counter_u64_fetch(kvm_t *kd, u_long base)
{
	uint64_t r, c;

	if (mp_ncpus == 0)
		if (_kvm_pcpu_init(kd) < 0)
			return (0);

	r = 0;
	for (int i = 0; i < mp_ncpus; i++) {
		if (kvm_read_zpcpu(kd, base, &c, sizeof(c), i) != sizeof(c))
			return (0);
		r += c;
	}

	return (r);
}