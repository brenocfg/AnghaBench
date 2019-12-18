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
struct physical {int dummy; } ;
struct TYPE_2__ {char* phone; int /*<<< orphan*/  timer; scalar_t__ delay; scalar_t__ id; int /*<<< orphan*/  state; } ;
struct cbcp {struct physical* p; TYPE_1__ fsm; scalar_t__ required; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBCP_CLOSED ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 

void
cbcp_Init(struct cbcp *cbcp, struct physical *p)
{
  cbcp->required = 0;
  cbcp->fsm.state = CBCP_CLOSED;
  cbcp->fsm.id = 0;
  cbcp->fsm.delay = 0;
  *cbcp->fsm.phone = '\0';
  memset(&cbcp->fsm.timer, '\0', sizeof cbcp->fsm.timer);
  cbcp->p = p;
}