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
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ u_int32_t ;
typedef  char u_char ;
struct mbuf {int dummy; } ;
struct fsmheader {int /*<<< orphan*/  length; } ;
struct fsm {TYPE_1__* link; int /*<<< orphan*/  LogLevel; } ;
struct TYPE_4__ {scalar_t__ his_magic; } ;
struct TYPE_3__ {TYPE_2__ lcp; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char* MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  lcp_RecvIdentification (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_append (struct mbuf*,char*,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_pullup (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ua_ntohl (char*,scalar_t__*) ; 

__attribute__((used)) static void
FsmRecvIdent(struct fsm *fp, struct fsmheader *lhp, struct mbuf *bp)
{
  u_int32_t magic;
  u_short len;
  u_char *cp;

  len = ntohs(lhp->length) - sizeof *lhp;
  if (len >= 4) {
    bp = m_pullup(m_append(bp, "", 1));
    cp = MBUF_CTOP(bp);
    ua_ntohl(cp, &magic);
    if (magic != fp->link->lcp.his_magic)
      log_Printf(fp->LogLevel, "%s: RecvIdent: magic 0x%08lx is wrong,"
                 " expecting 0x%08lx\n", fp->link->name, (u_long)magic,
                 (u_long)fp->link->lcp.his_magic);
    cp[len] = '\0';
    lcp_RecvIdentification(&fp->link->lcp, cp + 4);
  }
  m_freem(bp);
}