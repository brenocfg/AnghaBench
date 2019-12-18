#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct TYPE_6__ {int /*<<< orphan*/  unknownproto; } ;
struct TYPE_5__ {int /*<<< orphan*/  ifInDiscards; } ;
struct TYPE_7__ {TYPE_2__ stats; TYPE_1__ lqm; } ;
struct physical {TYPE_3__ hdlc; } ;
struct mbuf {int /*<<< orphan*/  m_len; } ;
struct link {int /*<<< orphan*/  lcp; } ;
struct bundle {int dummy; } ;
struct TYPE_8__ {struct mbuf* (* fn ) (struct bundle*,struct link*,struct mbuf*) ;int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 unsigned int DSIZE ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  MBUF_CTOP (struct mbuf*) ; 
 TYPE_4__* despatcher ; 
 int /*<<< orphan*/  hdlc_Protocol2Nam (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcp_SendProtoRej (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct physical* link2physical (struct link*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_pullup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_Prepend (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbuf* stub1 (struct bundle*,struct link*,struct mbuf*) ; 

__attribute__((used)) static void
Despatch(struct bundle *bundle, struct link *l, struct mbuf *bp, u_short proto)
{
  unsigned f;

  for (f = 0; f < DSIZE; f++)
    if (despatcher[f].proto == proto) {
      bp = (*despatcher[f].fn)(bundle, l, bp);
      break;
    }

  if (bp) {
    struct physical *p = link2physical(l);

    log_Printf(LogPHASE, "%s protocol 0x%04x (%s)\n",
               f == DSIZE ? "Unknown" : "Unexpected", proto,
               hdlc_Protocol2Nam(proto));
    bp = m_pullup(proto_Prepend(bp, proto, 0, 0));
    lcp_SendProtoRej(&l->lcp, MBUF_CTOP(bp), bp->m_len);
    if (p) {
      p->hdlc.lqm.ifInDiscards++;
      p->hdlc.stats.unknownproto++;
    }
    m_freem(bp);
  }
}