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
struct TYPE_2__ {int terminate; int /*<<< orphan*/  term_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 TYPE_1__ eloop ; 

void eloop_terminate(void)
{
	eloop.terminate = 1;
	SetEvent(eloop.term_event);
}