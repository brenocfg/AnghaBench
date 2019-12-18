#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct physical {int dummy; } ;
struct TYPE_10__ {TYPE_4__* dns; } ;
struct TYPE_7__ {int /*<<< orphan*/  dns_neg; } ;
struct TYPE_8__ {TYPE_2__ ns; } ;
struct compreq {int slots; int compcid; int /*<<< orphan*/  proto; } ;
struct TYPE_6__ {struct compreq s_addr; } ;
struct ipcp {int my_compproto; TYPE_5__ ns; TYPE_3__ cfg; scalar_t__ heis1172; TYPE_1__ my_ip; } ;
struct fsm_opt {int /*<<< orphan*/  data; } ;
struct fsm {int /*<<< orphan*/  reqid; int /*<<< orphan*/  link; } ;
struct TYPE_9__ {struct compreq s_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_CONFIGREQ ; 
 int /*<<< orphan*/  INC_FSM_OPT (scalar_t__,int,struct fsm_opt*) ; 
 scalar_t__ IsEnabled (int /*<<< orphan*/ ) ; 
 int MAX_FSM_OPT_LEN ; 
 int /*<<< orphan*/  MB_IPCPOUT ; 
 int /*<<< orphan*/  PROTO_VJCOMP ; 
 int /*<<< orphan*/  REJECTED (struct ipcp*,scalar_t__) ; 
 scalar_t__ TY_ADJUST_NS ; 
 scalar_t__ TY_COMPPROTO ; 
 scalar_t__ TY_IPADDR ; 
 scalar_t__ TY_PRIMARY_DNS ; 
 scalar_t__ TY_SECONDARY_DNS ; 
 struct ipcp* fsm2ipcp (struct fsm*) ; 
 int /*<<< orphan*/  fsm_Output (struct fsm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 struct physical* link2physical (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct compreq*,int) ; 
 int /*<<< orphan*/  physical_IsSync (struct physical*) ; 
 int /*<<< orphan*/  ua_htons (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
IpcpSendConfigReq(struct fsm *fp)
{
  /* Send config REQ please */
  struct physical *p = link2physical(fp->link);
  struct ipcp *ipcp = fsm2ipcp(fp);
  u_char buff[MAX_FSM_OPT_LEN];
  struct fsm_opt *o;

  o = (struct fsm_opt *)buff;

  if ((p && !physical_IsSync(p)) || !REJECTED(ipcp, TY_IPADDR)) {
    memcpy(o->data, &ipcp->my_ip.s_addr, 4);
    INC_FSM_OPT(TY_IPADDR, 6, o);
  }

  if (ipcp->my_compproto && !REJECTED(ipcp, TY_COMPPROTO)) {
    if (ipcp->heis1172) {
      u_int16_t proto = PROTO_VJCOMP;

      ua_htons(&proto, o->data);
      INC_FSM_OPT(TY_COMPPROTO, 4, o);
    } else {
      struct compreq req;

      req.proto = htons(ipcp->my_compproto >> 16);
      req.slots = (ipcp->my_compproto >> 8) & 255;
      req.compcid = ipcp->my_compproto & 1;
      memcpy(o->data, &req, 4);
      INC_FSM_OPT(TY_COMPPROTO, 6, o);
    }
  }

  if (IsEnabled(ipcp->cfg.ns.dns_neg)) {
    if (!REJECTED(ipcp, TY_PRIMARY_DNS - TY_ADJUST_NS)) {
      memcpy(o->data, &ipcp->ns.dns[0].s_addr, 4);
      INC_FSM_OPT(TY_PRIMARY_DNS, 6, o);
    }

    if (!REJECTED(ipcp, TY_SECONDARY_DNS - TY_ADJUST_NS)) {
      memcpy(o->data, &ipcp->ns.dns[1].s_addr, 4);
      INC_FSM_OPT(TY_SECONDARY_DNS, 6, o);
    }
  }

  fsm_Output(fp, CODE_CONFIGREQ, fp->reqid, buff, (u_char *)o - buff,
             MB_IPCPOUT);
}