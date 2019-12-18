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
typedef  int /*<<< orphan*/  u_char ;
struct mbuf {int /*<<< orphan*/  m_len; } ;
struct fsmheader {int code; int /*<<< orphan*/  id; int /*<<< orphan*/  length; } ;
struct fsmcodedesc {int /*<<< orphan*/  (* recv ) (struct fsm*,struct fsmheader*,struct mbuf*) ;scalar_t__ check_reqid; scalar_t__ inc_reqid; int /*<<< orphan*/  name; } ;
struct fsm {int min_code; int max_code; int /*<<< orphan*/  reqid; int /*<<< orphan*/  bundle; int /*<<< orphan*/  state; TYPE_1__* link; int /*<<< orphan*/  LogLevel; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_CODEREJ ; 
 scalar_t__ Enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsmcodedesc* FsmCodes ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  MB_UNKNOWN ; 
 int /*<<< orphan*/  OPT_IDCHECK ; 
 int /*<<< orphan*/  State2Nam (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_Output (struct fsm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,int,...) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 size_t m_length (struct mbuf*) ; 
 struct mbuf* m_prepend (struct mbuf*,struct fsmheader*,int,int /*<<< orphan*/ ) ; 
 struct mbuf* m_pullup (struct mbuf*) ; 
 struct mbuf* mbuf_Read (struct mbuf*,struct fsmheader*,int) ; 
 size_t ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fsm*,struct fsmheader*,struct mbuf*) ; 

void
fsm_Input(struct fsm *fp, struct mbuf *bp)
{
  size_t len;
  struct fsmheader lh;
  const struct fsmcodedesc *codep;

  len = m_length(bp);
  if (len < sizeof(struct fsmheader)) {
    m_freem(bp);
    return;
  }
  bp = mbuf_Read(bp, &lh, sizeof lh);

  if (ntohs(lh.length) > len) {
    log_Printf(LogWARN, "%s: Oops: Got %zu bytes but %d byte payload "
               "- dropped\n", fp->link->name, len, (int)ntohs(lh.length));
    m_freem(bp);
    return;
  }

  if (lh.code < fp->min_code || lh.code > fp->max_code ||
      lh.code > sizeof FsmCodes / sizeof *FsmCodes) {
    /*
     * Use a private id.  This is really a response-type packet, but we
     * MUST send a unique id for each REQ....
     */
    static u_char id;

    bp = m_prepend(bp, &lh, sizeof lh, 0);
    bp = m_pullup(bp);
    fsm_Output(fp, CODE_CODEREJ, id++, MBUF_CTOP(bp), bp->m_len, MB_UNKNOWN);
    m_freem(bp);
    return;
  }

  codep = FsmCodes + lh.code - 1;
  if (lh.id != fp->reqid && codep->check_reqid &&
      Enabled(fp->bundle, OPT_IDCHECK)) {
    log_Printf(fp->LogLevel, "%s: Recv%s(%d), dropped (expected %d)\n",
               fp->link->name, codep->name, lh.id, fp->reqid);
    return;
  }

  log_Printf(fp->LogLevel, "%s: Recv%s(%d) state = %s\n",
             fp->link->name, codep->name, lh.id, State2Nam(fp->state));

  if (codep->inc_reqid && (lh.id == fp->reqid ||
      (!Enabled(fp->bundle, OPT_IDCHECK) && codep->check_reqid)))
    fp->reqid++;	/* That's the end of that ``exchange''.... */

  (*codep->recv)(fp, &lh, bp);
}