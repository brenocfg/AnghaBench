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
typedef  long u_long ;
typedef  int u_int32_t ;
struct mbuf {int dummy; } ;
struct lcp {scalar_t__ his_magic; scalar_t__ want_magic; } ;
struct TYPE_5__ {int seq_recv; } ;
struct TYPE_6__ {TYPE_1__ echo; } ;
struct hdlc {TYPE_2__ lqm; } ;
struct fsm {TYPE_4__* link; } ;
struct echolqr {scalar_t__ magic; scalar_t__ signature; scalar_t__ sequence; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {struct hdlc hdlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 scalar_t__ SIGNATURE ; 
 struct lcp* fsm2lcp (struct fsm*) ; 
 TYPE_3__* link2physical (TYPE_4__*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,long,long,...) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 long m_length (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_Read (struct mbuf*,struct echolqr*,int) ; 
 void* ntohl (scalar_t__) ; 

struct mbuf *
lqr_RecvEcho(struct fsm *fp, struct mbuf *bp)
{
  struct hdlc *hdlc = &link2physical(fp->link)->hdlc;
  struct lcp *lcp = fsm2lcp(fp);
  struct echolqr lqr;

  if (m_length(bp) >= sizeof lqr) {
    m_freem(mbuf_Read(bp, &lqr, sizeof lqr));
    bp = NULL;
    lqr.magic = ntohl(lqr.magic);
    lqr.signature = ntohl(lqr.signature);
    lqr.sequence = ntohl(lqr.sequence);

    /* Tolerate echo replies with either magic number */
    if (lqr.magic != 0 && lqr.magic != lcp->his_magic &&
        lqr.magic != lcp->want_magic) {
      log_Printf(LogWARN, "%s: lqr_RecvEcho: Bad magic: expected 0x%08x,"
                 " got 0x%08x\n", fp->link->name, lcp->his_magic, lqr.magic);
      /*
       * XXX: We should send a terminate request. But poor implementations may
       *      die as a result.
       */
    }
    if (lqr.signature == SIGNATURE
	|| lqr.signature == lcp->want_magic) {			/* some implementations return the wrong magic */
      /* careful not to update lqm.echo.seq_recv with older values */
      if ((hdlc->lqm.echo.seq_recv > (u_int32_t)0 - 5 && lqr.sequence < 5) ||
          (hdlc->lqm.echo.seq_recv <= (u_int32_t)0 - 5 &&
           lqr.sequence > hdlc->lqm.echo.seq_recv))
        hdlc->lqm.echo.seq_recv = lqr.sequence;
    } else
      log_Printf(LogWARN, "lqr_RecvEcho: Got sig 0x%08lx, not 0x%08lx !\n",
                (u_long)lqr.signature, (u_long)SIGNATURE);
  } else
    log_Printf(LogWARN, "lqr_RecvEcho: Got packet size %zd, expecting %ld !\n",
              m_length(bp), (long)sizeof(struct echolqr));
  return bp;
}