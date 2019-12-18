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
struct TYPE_8__ {int ua_all; int ua_set; int /*<<< orphan*/  ua_type; } ;
struct TYPE_6__ {int initid; int targ_port; int /*<<< orphan*/  targ_mapped_lun; int /*<<< orphan*/  targ_lun; } ;
struct TYPE_7__ {TYPE_2__ nexus; int /*<<< orphan*/  msg_type; } ;
union ctl_ha_msg {TYPE_4__ ua; TYPE_3__ hdr; } ;
struct ctl_lun {int flags; int /*<<< orphan*/  lun; TYPE_1__* ctl_softc; int /*<<< orphan*/  lun_lock; } ;
struct ctl_be_lun {scalar_t__ ctl_lun; } ;
struct TYPE_5__ {scalar_t__ ha_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_HA_CHAN_CTL ; 
 scalar_t__ CTL_HA_MODE_XFER ; 
 int CTL_LUN_EJECTED ; 
 int CTL_LUN_NO_MEDIA ; 
 int CTL_LUN_REMOVABLE ; 
 int /*<<< orphan*/  CTL_MSG_UA ; 
 int /*<<< orphan*/  CTL_UA_MEDIUM_CHANGE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bzero (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ctl_est_ua_all (struct ctl_lun*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_ha_msg_send (int /*<<< orphan*/ ,union ctl_ha_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
ctl_lun_has_media(struct ctl_be_lun *be_lun)
{
	struct ctl_lun *lun = (struct ctl_lun *)be_lun->ctl_lun;
	union ctl_ha_msg msg;

	mtx_lock(&lun->lun_lock);
	lun->flags &= ~(CTL_LUN_NO_MEDIA | CTL_LUN_EJECTED);
	if (lun->flags & CTL_LUN_REMOVABLE)
		ctl_est_ua_all(lun, -1, CTL_UA_MEDIUM_CHANGE);
	mtx_unlock(&lun->lun_lock);
	if ((lun->flags & CTL_LUN_REMOVABLE) &&
	    lun->ctl_softc->ha_mode == CTL_HA_MODE_XFER) {
		bzero(&msg.ua, sizeof(msg.ua));
		msg.hdr.msg_type = CTL_MSG_UA;
		msg.hdr.nexus.initid = -1;
		msg.hdr.nexus.targ_port = -1;
		msg.hdr.nexus.targ_lun = lun->lun;
		msg.hdr.nexus.targ_mapped_lun = lun->lun;
		msg.ua.ua_all = 1;
		msg.ua.ua_set = 1;
		msg.ua.ua_type = CTL_UA_MEDIUM_CHANGE;
		ctl_ha_msg_send(CTL_HA_CHAN_CTL, &msg, sizeof(msg.ua),
		    M_WAITOK);
	}
	return (0);
}