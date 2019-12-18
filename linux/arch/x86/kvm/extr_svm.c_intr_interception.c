#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  irq_exits; } ;
struct TYPE_4__ {TYPE_1__ stat; } ;
struct vcpu_svm {TYPE_2__ vcpu; } ;

/* Variables and functions */

__attribute__((used)) static int intr_interception(struct vcpu_svm *svm)
{
	++svm->vcpu.stat.irq_exits;
	return 1;
}