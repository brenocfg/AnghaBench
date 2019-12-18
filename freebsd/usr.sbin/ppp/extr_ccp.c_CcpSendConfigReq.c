#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct fsm {int /*<<< orphan*/  reqid; TYPE_2__* link; int /*<<< orphan*/  bundle; } ;
struct TYPE_11__ {int id; int len; } ;
struct TYPE_13__ {TYPE_3__ hdr; } ;
struct ccp_opt {int algorithm; struct ccp_opt* next; TYPE_5__ val; } ;
struct TYPE_12__ {int algorithm; struct ccp_opt* opt; } ;
struct TYPE_14__ {int /*<<< orphan*/ * neg; } ;
struct ccp {scalar_t__ his_reject; int my_proto; TYPE_4__ out; TYPE_6__ cfg; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* OptInit ) (int /*<<< orphan*/ ,TYPE_5__*,TYPE_6__*) ;} ;
struct TYPE_15__ {size_t Neg; int id; TYPE_1__ o; scalar_t__ (* Usable ) (struct fsm*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_CONFIGREQ ; 
 scalar_t__ IsEnabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  MB_CCPOUT ; 
 unsigned int NALGORITHMS ; 
 int /*<<< orphan*/  REJECTED (struct ccp*,int) ; 
 TYPE_8__** algorithm ; 
 struct ccp* fsm2ccp (struct fsm*) ; 
 int /*<<< orphan*/  fsm_Output (struct fsm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 scalar_t__ stub1 (struct fsm*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_5__*,TYPE_6__*) ; 

__attribute__((used)) static void
CcpSendConfigReq(struct fsm *fp)
{
  /* Send config REQ please */
  struct ccp *ccp = fsm2ccp(fp);
  struct ccp_opt **o;
  u_char *cp, buff[100];
  unsigned f;
  int alloc;

  cp = buff;
  o = &ccp->out.opt;
  alloc = ccp->his_reject == 0 && ccp->out.opt == NULL;
  ccp->my_proto = -1;
  ccp->out.algorithm = -1;
  for (f = 0; f < NALGORITHMS; f++)
    if (IsEnabled(ccp->cfg.neg[algorithm[f]->Neg]) &&
        !REJECTED(ccp, algorithm[f]->id) &&
        (*algorithm[f]->Usable)(fp)) {

      if (!alloc)
        for (o = &ccp->out.opt; *o != NULL; o = &(*o)->next)
          if ((*o)->val.hdr.id == algorithm[f]->id && (*o)->algorithm == (int)f)
            break;

      if (alloc || *o == NULL) {
        if ((*o = (struct ccp_opt *)malloc(sizeof(struct ccp_opt))) == NULL) {
	  log_Printf(LogERROR, "%s: Not enough memory for CCP REQ !\n",
		     fp->link->name);
	  break;
	}
        (*o)->val.hdr.id = algorithm[f]->id;
        (*o)->val.hdr.len = 2;
        (*o)->next = NULL;
        (*o)->algorithm = f;
        (*algorithm[f]->o.OptInit)(fp->bundle, &(*o)->val, &ccp->cfg);
      }

      if (cp + (*o)->val.hdr.len > buff + sizeof buff) {
        log_Printf(LogERROR, "%s: CCP REQ buffer overrun !\n", fp->link->name);
        break;
      }
      memcpy(cp, &(*o)->val, (*o)->val.hdr.len);
      cp += (*o)->val.hdr.len;

      ccp->my_proto = (*o)->val.hdr.id;
      ccp->out.algorithm = f;

      if (alloc)
        o = &(*o)->next;
    }

  fsm_Output(fp, CODE_CONFIGREQ, fp->reqid, buff, cp - buff, MB_CCPOUT);
}