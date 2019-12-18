#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct dvd_authinfo {int /*<<< orphan*/  region; int /*<<< orphan*/  format; int /*<<< orphan*/  agid; int /*<<< orphan*/  lba; int /*<<< orphan*/  keychal; } ;
struct TYPE_18__ {int /*<<< orphan*/  pdrc; } ;
struct TYPE_17__ {int /*<<< orphan*/  agid; } ;
struct TYPE_16__ {int /*<<< orphan*/  agid; } ;
struct TYPE_15__ {int /*<<< orphan*/  lba; int /*<<< orphan*/  agid; } ;
struct TYPE_14__ {int /*<<< orphan*/  key; int /*<<< orphan*/  agid; } ;
struct TYPE_13__ {int /*<<< orphan*/  agid; } ;
struct TYPE_12__ {int /*<<< orphan*/  agid; } ;
struct TYPE_11__ {int /*<<< orphan*/  chal; int /*<<< orphan*/  agid; } ;
struct TYPE_19__ {int type; TYPE_8__ hrpcs; TYPE_7__ lsa; TYPE_6__ lsasf; TYPE_5__ lstk; TYPE_4__ hsk; TYPE_3__ lsc; TYPE_2__ lsk; TYPE_1__ hsc; } ;
typedef  TYPE_9__ l_dvd_authinfo ;

/* Variables and functions */
 int DVDIOCREPORTKEY ; 
 int DVDIOCSENDKEY ; 
 int /*<<< orphan*/  DVD_INVALIDATE_AGID ; 
 int /*<<< orphan*/  DVD_REPORT_AGID ; 
 int /*<<< orphan*/  DVD_REPORT_ASF ; 
 int /*<<< orphan*/  DVD_REPORT_CHALLENGE ; 
 int /*<<< orphan*/  DVD_REPORT_KEY1 ; 
 int /*<<< orphan*/  DVD_REPORT_RPC ; 
 int /*<<< orphan*/  DVD_REPORT_TITLE_KEY ; 
 int /*<<< orphan*/  DVD_SEND_CHALLENGE ; 
 int /*<<< orphan*/  DVD_SEND_KEY2 ; 
 int /*<<< orphan*/  DVD_SEND_RPC ; 
 int EINVAL ; 
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
linux_to_bsd_dvd_authinfo(l_dvd_authinfo *lp, int *bcode,
    struct dvd_authinfo *bp)
{
	switch (lp->type) {
	case LINUX_DVD_LU_SEND_AGID:
		*bcode = DVDIOCREPORTKEY;
		bp->format = DVD_REPORT_AGID;
		bp->agid = lp->lsa.agid;
		break;
	case LINUX_DVD_HOST_SEND_CHALLENGE:
		*bcode = DVDIOCSENDKEY;
		bp->format = DVD_SEND_CHALLENGE;
		bp->agid = lp->hsc.agid;
		memcpy(bp->keychal, lp->hsc.chal, 10);
		break;
	case LINUX_DVD_LU_SEND_KEY1:
		*bcode = DVDIOCREPORTKEY;
		bp->format = DVD_REPORT_KEY1;
		bp->agid = lp->lsk.agid;
		break;
	case LINUX_DVD_LU_SEND_CHALLENGE:
		*bcode = DVDIOCREPORTKEY;
		bp->format = DVD_REPORT_CHALLENGE;
		bp->agid = lp->lsc.agid;
		break;
	case LINUX_DVD_HOST_SEND_KEY2:
		*bcode = DVDIOCSENDKEY;
		bp->format = DVD_SEND_KEY2;
		bp->agid = lp->hsk.agid;
		memcpy(bp->keychal, lp->hsk.key, 5);
		break;
	case LINUX_DVD_LU_SEND_TITLE_KEY:
		*bcode = DVDIOCREPORTKEY;
		bp->format = DVD_REPORT_TITLE_KEY;
		bp->agid = lp->lstk.agid;
		bp->lba = lp->lstk.lba;
		break;
	case LINUX_DVD_LU_SEND_ASF:
		*bcode = DVDIOCREPORTKEY;
		bp->format = DVD_REPORT_ASF;
		bp->agid = lp->lsasf.agid;
		break;
	case LINUX_DVD_INVALIDATE_AGID:
		*bcode = DVDIOCREPORTKEY;
		bp->format = DVD_INVALIDATE_AGID;
		bp->agid = lp->lsa.agid;
		break;
	case LINUX_DVD_LU_SEND_RPC_STATE:
		*bcode = DVDIOCREPORTKEY;
		bp->format = DVD_REPORT_RPC;
		break;
	case LINUX_DVD_HOST_SEND_RPC_STATE:
		*bcode = DVDIOCSENDKEY;
		bp->format = DVD_SEND_RPC;
		bp->region = lp->hrpcs.pdrc;
		break;
	default:
		return (EINVAL);
	}
	return (0);
}