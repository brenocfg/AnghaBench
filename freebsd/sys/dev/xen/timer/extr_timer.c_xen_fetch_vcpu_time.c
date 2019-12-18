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
typedef  int /*<<< orphan*/  uint64_t ;
struct vcpu_info {int /*<<< orphan*/  time; } ;
struct pvclock_vcpu_time_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pvclock_get_timecount (struct pvclock_vcpu_time_info*) ; 

__attribute__((used)) static uint64_t
xen_fetch_vcpu_time(struct vcpu_info *vcpu)
{
	struct pvclock_vcpu_time_info *time;

	time = (struct pvclock_vcpu_time_info *) &vcpu->time;

	return (pvclock_get_timecount(time));
}