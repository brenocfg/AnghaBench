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
struct serial {int /*<<< orphan*/  async_context; int /*<<< orphan*/  (* async_handler ) (struct serial*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  async_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOTHING_SCHEDULED ; 
 int /*<<< orphan*/  reschedule (struct serial*) ; 
 int /*<<< orphan*/  stub1 (struct serial*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
push_event (void *context)
{
  struct serial *scb = context;
  scb->async_state = NOTHING_SCHEDULED; /* Timers are one-off */
  scb->async_handler (scb, scb->async_context);
  /* re-schedule */
  reschedule (scb);
}