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
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct mbuf {int dummy; } ;
struct lcp {scalar_t__ his_magic; int /*<<< orphan*/  want_magic; } ;
struct fsmheader {int /*<<< orphan*/  length; int /*<<< orphan*/  id; } ;
struct fsm {scalar_t__ state; TYPE_1__* link; int /*<<< orphan*/  LogLevel; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_ECHOREP ; 
 int /*<<< orphan*/ * MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  MB_ECHOIN ; 
 int /*<<< orphan*/  MB_ECHOOUT ; 
 scalar_t__ ST_OPENED ; 
 struct lcp* fsm2lcp (struct fsm*) ; 
 int /*<<< orphan*/  fsm_Output (struct fsm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_pullup (struct mbuf*) ; 
 int /*<<< orphan*/  m_settype (struct mbuf*,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ua_htonl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ua_ntohl (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static void
FsmRecvEchoReq(struct fsm *fp, struct fsmheader *lhp, struct mbuf *bp)
{
  struct lcp *lcp = fsm2lcp(fp);
  u_char *cp;
  u_int32_t magic;

  bp = m_pullup(bp);
  m_settype(bp, MB_ECHOIN);

  if (lcp && ntohs(lhp->length) - sizeof *lhp >= 4) {
    cp = MBUF_CTOP(bp);
    ua_ntohl(cp, &magic);
    if (magic != lcp->his_magic) {
      log_Printf(fp->LogLevel, "%s: RecvEchoReq: magic 0x%08lx is wrong,"
                 " expecting 0x%08lx\n", fp->link->name, (u_long)magic,
                 (u_long)lcp->his_magic);
      /* XXX: We should send terminate request */
    }
    if (fp->state == ST_OPENED) {
      ua_htonl(&lcp->want_magic, cp);		/* local magic */
      fsm_Output(fp, CODE_ECHOREP, lhp->id, cp,
                 ntohs(lhp->length) - sizeof *lhp, MB_ECHOOUT);
    }
  }
  m_freem(bp);
}