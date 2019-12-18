#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct dvd_authinfo {int /*<<< orphan*/  rpc_scheme; int /*<<< orphan*/  region; int /*<<< orphan*/  user_rsts; int /*<<< orphan*/  vend_rsts; int /*<<< orphan*/  reg_type; int /*<<< orphan*/  asf; int /*<<< orphan*/  cgms; int /*<<< orphan*/  cp_sec; int /*<<< orphan*/  cpm; int /*<<< orphan*/  keychal; int /*<<< orphan*/  agid; } ;
struct TYPE_14__ {int /*<<< orphan*/  rpc_scheme; int /*<<< orphan*/  region_mask; int /*<<< orphan*/  ucca; int /*<<< orphan*/  vra; int /*<<< orphan*/  type; } ;
struct TYPE_13__ {int /*<<< orphan*/  asf; } ;
struct TYPE_12__ {int /*<<< orphan*/  cgms; int /*<<< orphan*/  cp_sec; int /*<<< orphan*/  cpm; int /*<<< orphan*/  title_key; } ;
struct TYPE_11__ {int /*<<< orphan*/  chal; } ;
struct TYPE_10__ {int /*<<< orphan*/  key; } ;
struct TYPE_9__ {int /*<<< orphan*/  agid; } ;
struct TYPE_15__ {int type; TYPE_6__ lrpcs; TYPE_5__ lsasf; TYPE_4__ lstk; TYPE_3__ lsc; TYPE_2__ lsk; TYPE_1__ lsa; } ;
typedef  TYPE_7__ l_dvd_authinfo ;

/* Variables and functions */
 int EINVAL ; 
 int LINUX_DVD_AUTH_ESTABLISHED ; 
#define  LINUX_DVD_HOST_SEND_CHALLENGE 137 
#define  LINUX_DVD_HOST_SEND_KEY2 136 
#define  LINUX_DVD_HOST_SEND_RPC_STATE 135 
#define  LINUX_DVD_INVALIDATE_AGID 134 
#define  LINUX_DVD_LU_SEND_AGID 133 
#define  LINUX_DVD_LU_SEND_ASF 132 
#define  LINUX_DVD_LU_SEND_CHALLENGE 131 
#define  LINUX_DVD_LU_SEND_KEY1 130 
#define  LINUX_DVD_LU_SEND_RPC_STATE 129 
#define  LINUX_DVD_LU_SEND_TITLE_KEY 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bsd_to_linux_dvd_authinfo(struct dvd_authinfo *bp, l_dvd_authinfo *lp)
{
	switch (lp->type) {
	case LINUX_DVD_LU_SEND_AGID:
		lp->lsa.agid = bp->agid;
		break;
	case LINUX_DVD_HOST_SEND_CHALLENGE:
		lp->type = LINUX_DVD_LU_SEND_KEY1;
		break;
	case LINUX_DVD_LU_SEND_KEY1:
		memcpy(lp->lsk.key, bp->keychal, sizeof(lp->lsk.key));
		break;
	case LINUX_DVD_LU_SEND_CHALLENGE:
		memcpy(lp->lsc.chal, bp->keychal, sizeof(lp->lsc.chal));
		break;
	case LINUX_DVD_HOST_SEND_KEY2:
		lp->type = LINUX_DVD_AUTH_ESTABLISHED;
		break;
	case LINUX_DVD_LU_SEND_TITLE_KEY:
		memcpy(lp->lstk.title_key, bp->keychal,
		    sizeof(lp->lstk.title_key));
		lp->lstk.cpm = bp->cpm;
		lp->lstk.cp_sec = bp->cp_sec;
		lp->lstk.cgms = bp->cgms;
		break;
	case LINUX_DVD_LU_SEND_ASF:
		lp->lsasf.asf = bp->asf;
		break;
	case LINUX_DVD_INVALIDATE_AGID:
		break;
	case LINUX_DVD_LU_SEND_RPC_STATE:
		lp->lrpcs.type = bp->reg_type;
		lp->lrpcs.vra = bp->vend_rsts;
		lp->lrpcs.ucca = bp->user_rsts;
		lp->lrpcs.region_mask = bp->region;
		lp->lrpcs.rpc_scheme = bp->rpc_scheme;
		break;
	case LINUX_DVD_HOST_SEND_RPC_STATE:
		break;
	default:
		return (EINVAL);
	}
	return (0);
}