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
struct ub_event {int dummy; } ;
struct timeval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_EVENT (struct ub_event*) ; 
 int signal_add (int /*<<< orphan*/ ,struct timeval*) ; 

int
ub_signal_add(struct ub_event* ev, struct timeval* tv)
{
	return signal_add(AS_EVENT(ev), tv);
}