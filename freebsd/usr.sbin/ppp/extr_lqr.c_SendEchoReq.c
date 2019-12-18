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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_8__ {int /*<<< orphan*/  link; } ;
struct lcp {TYPE_4__ fsm; int /*<<< orphan*/  want_magic; } ;
struct TYPE_5__ {int /*<<< orphan*/  seq_sent; } ;
struct TYPE_6__ {TYPE_1__ echo; } ;
struct hdlc {TYPE_2__ lqm; } ;
struct echolqr {void* sequence; void* signature; void* magic; } ;
struct TYPE_7__ {struct hdlc hdlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_ECHOREQ ; 
 int /*<<< orphan*/  MB_ECHOOUT ; 
 int /*<<< orphan*/  SIGNATURE ; 
 int /*<<< orphan*/  fsm_Output (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 TYPE_3__* link2physical (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SendEchoReq(struct lcp *lcp)
{
  struct hdlc *hdlc = &link2physical(lcp->fsm.link)->hdlc;
  struct echolqr echo;

  echo.magic = htonl(lcp->want_magic);
  echo.signature = htonl(SIGNATURE);
  echo.sequence = htonl(hdlc->lqm.echo.seq_sent);
  fsm_Output(&lcp->fsm, CODE_ECHOREQ, hdlc->lqm.echo.seq_sent++,
            (u_char *)&echo, sizeof echo, MB_ECHOOUT);
}