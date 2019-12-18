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
typedef  size_t u_int ;
struct slcompress {int last_recv; int last_xmit; int /*<<< orphan*/  flags; struct cstate* last_cs; struct cstate* tstate; } ;
struct cstate {size_t cs_id; struct cstate* cs_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLF_TOSS ; 
 int /*<<< orphan*/  memset (struct slcompress*,char,int) ; 

void
sl_compress_init(struct slcompress *comp, int max_state)
{
  register u_int i;
  register struct cstate *tstate = comp->tstate;

  memset(comp, '\0', sizeof *comp);
  for (i = max_state; i > 0; --i) {
    tstate[i].cs_id = i;
    tstate[i].cs_next = &tstate[i - 1];
  }
  tstate[0].cs_next = &tstate[max_state];
  tstate[0].cs_id = 0;
  comp->last_cs = &tstate[0];
  comp->last_recv = 255;
  comp->last_xmit = 255;
  comp->flags = SLF_TOSS;
}