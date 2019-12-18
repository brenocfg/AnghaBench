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
typedef  int /*<<< orphan*/  u_char ;
struct physical {int dummy; } ;
struct ipv6cp {int /*<<< orphan*/  my_ifid; } ;
struct fsm_opt {int /*<<< orphan*/  data; } ;
struct fsm {int /*<<< orphan*/  reqid; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_CONFIGREQ ; 
 int /*<<< orphan*/  INC_FSM_OPT (int /*<<< orphan*/ ,int,struct fsm_opt*) ; 
 int IPV6CP_IFIDLEN ; 
 int /*<<< orphan*/  MB_IPV6CPOUT ; 
 int /*<<< orphan*/  REJECTED (struct ipv6cp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TY_TOKEN ; 
 struct ipv6cp* fsm2ipv6cp (struct fsm*) ; 
 int /*<<< orphan*/  fsm_Output (struct fsm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct physical* link2physical (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  physical_IsSync (struct physical*) ; 

__attribute__((used)) static void
ipv6cp_SendConfigReq(struct fsm *fp)
{
  /* Send config REQ please */
  struct physical *p = link2physical(fp->link);
  struct ipv6cp *ipv6cp = fsm2ipv6cp(fp);
  u_char buff[IPV6CP_IFIDLEN+2];
  struct fsm_opt *o;

  o = (struct fsm_opt *)buff;

  if ((p && !physical_IsSync(p)) || !REJECTED(ipv6cp, TY_TOKEN)) {
    memcpy(o->data, ipv6cp->my_ifid, IPV6CP_IFIDLEN);
    INC_FSM_OPT(TY_TOKEN, IPV6CP_IFIDLEN + 2, o);
  }

  fsm_Output(fp, CODE_CONFIGREQ, fp->reqid, buff, (u_char *)o - buff,
             MB_IPV6CPOUT);
}