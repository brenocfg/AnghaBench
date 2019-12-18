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
struct deflate_state {int /*<<< orphan*/  cx; scalar_t__ uncomp_rec; scalar_t__ seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogCCP ; 
 int /*<<< orphan*/  deflateReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
DeflateResetOutput(void *v)
{
  struct deflate_state *state = (struct deflate_state *)v;

  state->seqno = 0;
  state->uncomp_rec = 0;
  deflateReset(&state->cx);
  log_Printf(LogCCP, "Deflate: Output channel reset\n");

  return 1;		/* Ask FSM to ACK */
}