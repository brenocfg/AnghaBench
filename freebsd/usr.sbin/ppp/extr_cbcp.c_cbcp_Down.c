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
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct cbcp {scalar_t__ required; TYPE_1__ fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBCP_CLOSED ; 
 int /*<<< orphan*/  cbcp_NewPhase (struct cbcp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_Stop (int /*<<< orphan*/ *) ; 

void
cbcp_Down(struct cbcp *cbcp)
{
  timer_Stop(&cbcp->fsm.timer);
  cbcp_NewPhase(cbcp, CBCP_CLOSED);
  cbcp->required = 0;
}