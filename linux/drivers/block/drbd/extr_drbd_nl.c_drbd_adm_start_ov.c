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
struct start_ov_parms {int ov_start_sector; int /*<<< orphan*/  ov_stop_sector; } ;
struct sk_buff {int dummy; } ;
struct genl_info {scalar_t__* attrs; } ;
struct drbd_device {int ov_start_sector; int /*<<< orphan*/  flags; int /*<<< orphan*/  misc_wait; int /*<<< orphan*/  ov_stop_sector; } ;
struct drbd_config_context {TYPE_1__* resource; int /*<<< orphan*/  reply_skb; struct drbd_device* device; } ;
typedef  enum drbd_ret_code { ____Placeholder_drbd_ret_code } drbd_ret_code ;
struct TYPE_2__ {int /*<<< orphan*/  adm_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_IO ; 
 int BM_SECT_PER_BIT ; 
 int /*<<< orphan*/  C_VERIFY_S ; 
 int /*<<< orphan*/  DRBD_ADM_NEED_MINOR ; 
 size_t DRBD_NLA_START_OV_PARMS ; 
 int ERR_MANDATORY_TAG ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  NS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULLONG_MAX ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  drbd_adm_finish (struct drbd_config_context*,struct genl_info*,int) ; 
 int drbd_adm_prepare (struct drbd_config_context*,struct sk_buff*,struct genl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_msg_put_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drbd_request_state (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_resume_io (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_suspend_io (struct drbd_device*) ; 
 int /*<<< orphan*/  from_attrs_err_to_txt (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int start_ov_parms_from_attrs (struct start_ov_parms*,struct genl_info*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int drbd_adm_start_ov(struct sk_buff *skb, struct genl_info *info)
{
	struct drbd_config_context adm_ctx;
	struct drbd_device *device;
	enum drbd_ret_code retcode;
	struct start_ov_parms parms;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	if (!adm_ctx.reply_skb)
		return retcode;
	if (retcode != NO_ERROR)
		goto out;

	device = adm_ctx.device;

	/* resume from last known position, if possible */
	parms.ov_start_sector = device->ov_start_sector;
	parms.ov_stop_sector = ULLONG_MAX;
	if (info->attrs[DRBD_NLA_START_OV_PARMS]) {
		int err = start_ov_parms_from_attrs(&parms, info);
		if (err) {
			retcode = ERR_MANDATORY_TAG;
			drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
			goto out;
		}
	}
	mutex_lock(&adm_ctx.resource->adm_mutex);

	/* w_make_ov_request expects position to be aligned */
	device->ov_start_sector = parms.ov_start_sector & ~(BM_SECT_PER_BIT-1);
	device->ov_stop_sector = parms.ov_stop_sector;

	/* If there is still bitmap IO pending, e.g. previous resync or verify
	 * just being finished, wait for it before requesting a new resync. */
	drbd_suspend_io(device);
	wait_event(device->misc_wait, !test_bit(BITMAP_IO, &device->flags));
	retcode = drbd_request_state(device, NS(conn, C_VERIFY_S));
	drbd_resume_io(device);

	mutex_unlock(&adm_ctx.resource->adm_mutex);
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	return 0;
}