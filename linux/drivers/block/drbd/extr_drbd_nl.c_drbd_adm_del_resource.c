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
struct sk_buff {int dummy; } ;
struct genl_info {int dummy; } ;
struct drbd_resource {int /*<<< orphan*/  adm_mutex; } ;
struct drbd_config_context {struct drbd_resource* resource; int /*<<< orphan*/  reply_skb; } ;
typedef  enum drbd_ret_code { ____Placeholder_drbd_ret_code } drbd_ret_code ;

/* Variables and functions */
 int /*<<< orphan*/  DRBD_ADM_NEED_RESOURCE ; 
 int NO_ERROR ; 
 int adm_del_resource (struct drbd_resource*) ; 
 int /*<<< orphan*/  drbd_adm_finish (struct drbd_config_context*,struct genl_info*,int) ; 
 int drbd_adm_prepare (struct drbd_config_context*,struct sk_buff*,struct genl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drbd_adm_del_resource(struct sk_buff *skb, struct genl_info *info)
{
	struct drbd_config_context adm_ctx;
	struct drbd_resource *resource;
	enum drbd_ret_code retcode;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_RESOURCE);
	if (!adm_ctx.reply_skb)
		return retcode;
	if (retcode != NO_ERROR)
		goto finish;
	resource = adm_ctx.resource;

	mutex_lock(&resource->adm_mutex);
	retcode = adm_del_resource(resource);
	mutex_unlock(&resource->adm_mutex);
finish:
	drbd_adm_finish(&adm_ctx, info, retcode);
	return 0;
}