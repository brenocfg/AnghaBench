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
typedef  scalar_t__ uint32_t ;
struct hdaa_audio_ctl {int left; int right; int dir; int /*<<< orphan*/  index; TYPE_1__* widget; scalar_t__ muted; scalar_t__ forcemute; } ;
typedef  int /*<<< orphan*/  nid_t ;
struct TYPE_2__ {int /*<<< orphan*/  devinfo; int /*<<< orphan*/  nid; } ;

/* Variables and functions */
 int HDAA_AMP_LEFT_MUTED (scalar_t__) ; 
 scalar_t__ HDAA_AMP_MUTE_DEFAULT ; 
 int HDAA_AMP_RIGHT_MUTED (scalar_t__) ; 
 int HDAA_AMP_VOL_DEFAULT ; 
 int HDAA_CTL_IN ; 
 int HDAA_CTL_OUT ; 
 int /*<<< orphan*/  hdaa_audio_ctl_amp_set_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 

__attribute__((used)) static void
hdaa_audio_ctl_amp_set(struct hdaa_audio_ctl *ctl, uint32_t mute,
						int left, int right)
{
	nid_t nid;
	int lmute, rmute;

	nid = ctl->widget->nid;

	/* Save new values if valid. */
	if (mute != HDAA_AMP_MUTE_DEFAULT)
		ctl->muted = mute;
	if (left != HDAA_AMP_VOL_DEFAULT)
		ctl->left = left;
	if (right != HDAA_AMP_VOL_DEFAULT)
		ctl->right = right;
	/* Prepare effective values */
	if (ctl->forcemute) {
		lmute = 1;
		rmute = 1;
		left = 0;
		right = 0;
	} else {
		lmute = HDAA_AMP_LEFT_MUTED(ctl->muted);
		rmute = HDAA_AMP_RIGHT_MUTED(ctl->muted);
		left = ctl->left;
		right = ctl->right;
	}
	/* Apply effective values */
	if (ctl->dir & HDAA_CTL_OUT)
		hdaa_audio_ctl_amp_set_internal(ctl->widget->devinfo, nid, ctl->index,
		    lmute, rmute, left, right, 0);
	if (ctl->dir & HDAA_CTL_IN)
		hdaa_audio_ctl_amp_set_internal(ctl->widget->devinfo, nid, ctl->index,
		    lmute, rmute, left, right, 1);
}