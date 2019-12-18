#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct physical {int dummy; } ;
struct mbuf {int dummy; } ;
struct link {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  active; } ;
struct TYPE_3__ {TYPE_2__ mp; } ;
struct bundle {TYPE_1__ ncp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  MB_MPIN ; 
 struct physical* link2physical (struct link*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  m_settype (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_Assemble (TYPE_2__*,struct mbuf*,struct physical*) ; 

struct mbuf *
mp_Input(struct bundle *bundle, struct link *l, struct mbuf *bp)
{
  struct physical *p = link2physical(l);

  if (!bundle->ncp.mp.active)
    /* Let someone else deal with it ! */
    return bp;

  if (p == NULL) {
    log_Printf(LogWARN, "DecodePacket: Can't do MP inside MP !\n");
    m_freem(bp);
  } else {
    m_settype(bp, MB_MPIN);
    mp_Assemble(&bundle->ncp.mp, bp, p);
  }

  return NULL;
}