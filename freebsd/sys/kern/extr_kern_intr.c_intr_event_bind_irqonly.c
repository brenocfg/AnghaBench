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
struct intr_event {int dummy; } ;

/* Variables and functions */
 int _intr_event_bind (struct intr_event*,int,int,int) ; 

int
intr_event_bind_irqonly(struct intr_event *ie, int cpu)
{

	return (_intr_event_bind(ie, cpu, true, false));
}