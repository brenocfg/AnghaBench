#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct fsmheader {int code; int id; int /*<<< orphan*/  length; } ;
typedef  struct fsmheader u_char ;
struct mbuf {int dummy; } ;
struct fsm_opt_hdr {int dummy; } ;
struct fsm {TYPE_2__* link; int /*<<< orphan*/  proto; int /*<<< orphan*/  bundle; int /*<<< orphan*/  LogLevel; TYPE_1__* fn; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int /*<<< orphan*/  lcp; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* DecodeConfig ) (struct fsm*,struct fsmheader*,struct fsmheader*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
#define  CODE_CONFIGACK 131 
#define  CODE_CONFIGNAK 130 
#define  CODE_CONFIGREJ 129 
#define  CODE_CONFIGREQ 128 
 int /*<<< orphan*/  Code2Nam (int) ; 
 scalar_t__ LINK_QUEUES (TYPE_2__*) ; 
 int /*<<< orphan*/  LogDEBUG ; 
 scalar_t__ MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  MODE_NOP ; 
 int /*<<< orphan*/  State2Nam (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  lcp_SendIdentification (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_PushPacket (TYPE_2__*,struct mbuf*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_DumpBp (int /*<<< orphan*/ ,char*,struct mbuf*) ; 
 scalar_t__ log_IsKept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 struct mbuf* m_get (int,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct fsmheader*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct fsm*,struct fsmheader*,struct fsmheader*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
fsm_Output(struct fsm *fp, u_int code, u_int id, u_char *ptr, unsigned count,
           int mtype)
{
  int plen;
  struct fsmheader lh;
  struct mbuf *bp;

  if (log_IsKept(fp->LogLevel)) {
    log_Printf(fp->LogLevel, "%s: Send%s(%d) state = %s\n",
              fp->link->name, Code2Nam(code), id, State2Nam(fp->state));
    switch (code) {
      case CODE_CONFIGREQ:
      case CODE_CONFIGACK:
      case CODE_CONFIGREJ:
      case CODE_CONFIGNAK:
        (*fp->fn->DecodeConfig)(fp, ptr, ptr + count, MODE_NOP, NULL);
        if (count < sizeof(struct fsm_opt_hdr))
          log_Printf(fp->LogLevel, "  [EMPTY]\n");
        break;
    }
  }

  plen = sizeof(struct fsmheader) + count;
  lh.code = code;
  lh.id = id;
  lh.length = htons(plen);
  bp = m_get(plen, mtype);
  memcpy(MBUF_CTOP(bp), &lh, sizeof(struct fsmheader));
  if (count)
    memcpy(MBUF_CTOP(bp) + sizeof(struct fsmheader), ptr, count);
  log_DumpBp(LogDEBUG, "fsm_Output", bp);
  link_PushPacket(fp->link, bp, fp->bundle, LINK_QUEUES(fp->link) - 1,
                  fp->proto);

  if (code == CODE_CONFIGREJ)
    lcp_SendIdentification(&fp->link->lcp);
}