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
struct kinfo_proc {int dummy; } ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 char** kvm_argv (int /*<<< orphan*/ *,struct kinfo_proc const*,int /*<<< orphan*/ ,int) ; 

char **
kvm_getargv(kvm_t *kd, const struct kinfo_proc *kp, int nchr)
{
	return (kvm_argv(kd, kp, 0, nchr));
}