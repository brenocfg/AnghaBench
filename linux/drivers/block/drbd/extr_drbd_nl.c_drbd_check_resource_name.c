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
struct drbd_config_context {char* resource_name; int /*<<< orphan*/  reply_skb; } ;
typedef  enum drbd_ret_code { ____Placeholder_drbd_ret_code } drbd_ret_code ;

/* Variables and functions */
 int ERR_INVALID_REQUEST ; 
 int ERR_MANDATORY_TAG ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  drbd_msg_put_info (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static enum drbd_ret_code
drbd_check_resource_name(struct drbd_config_context *adm_ctx)
{
	const char *name = adm_ctx->resource_name;
	if (!name || !name[0]) {
		drbd_msg_put_info(adm_ctx->reply_skb, "resource name missing");
		return ERR_MANDATORY_TAG;
	}
	/* if we want to use these in sysfs/configfs/debugfs some day,
	 * we must not allow slashes */
	if (strchr(name, '/')) {
		drbd_msg_put_info(adm_ctx->reply_skb, "invalid resource name");
		return ERR_INVALID_REQUEST;
	}
	return NO_ERROR;
}