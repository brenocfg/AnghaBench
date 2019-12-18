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
 int kvm_cp_time_cached ; 
 int /*<<< orphan*/  kvm_cp_time_nl ; 
 scalar_t__ kvm_nlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_kvm_cp_time_init(kvm_t *kd)
{

	if (kvm_nlist(kd, kvm_cp_time_nl) < 0)
		return (-1);
	kvm_cp_time_cached = 1;
	return (0);
}