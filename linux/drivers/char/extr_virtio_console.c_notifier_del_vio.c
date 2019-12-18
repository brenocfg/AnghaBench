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
struct hvc_struct {scalar_t__ irq_requested; } ;

/* Variables and functions */

__attribute__((used)) static void notifier_del_vio(struct hvc_struct *hp, int data)
{
	hp->irq_requested = 0;
}