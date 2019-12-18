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
struct pred1_state {int /*<<< orphan*/  dict; scalar_t__ hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogCCP ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 

__attribute__((used)) static int
Pred1ResetOutput(void *v)
{
  struct pred1_state *state = (struct pred1_state *)v;
  state->hash = 0;
  memset(state->dict, '\0', sizeof state->dict);
  log_Printf(LogCCP, "Predictor1: Output channel reset\n");

  return 1;		/* Ask FSM to ACK */
}