#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  as_uint64; } ;
struct kvm_vcpu_hv_stimer {TYPE_1__ config; } ;

/* Variables and functions */

__attribute__((used)) static int stimer_get_config(struct kvm_vcpu_hv_stimer *stimer, u64 *pconfig)
{
	*pconfig = stimer->config.as_uint64;
	return 0;
}