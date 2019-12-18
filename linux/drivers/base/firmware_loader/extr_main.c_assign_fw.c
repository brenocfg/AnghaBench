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
struct fw_priv {int /*<<< orphan*/  ref; int /*<<< orphan*/  fw_name; TYPE_1__* fwc; int /*<<< orphan*/  size; } ;
struct firmware {struct fw_priv* priv; } ;
struct device {int dummy; } ;
typedef  enum fw_opt { ____Placeholder_fw_opt } fw_opt ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ FW_LOADER_START_CACHE ; 
 int FW_OPT_NOCACHE ; 
 int FW_OPT_UEVENT ; 
 int fw_add_devm_name (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ fw_cache_piggyback_on_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_lock ; 
 int /*<<< orphan*/  fw_set_page_data (struct fw_priv*,struct firmware*) ; 
 scalar_t__ fw_state_is_aborted (struct fw_priv*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int assign_fw(struct firmware *fw, struct device *device,
	      enum fw_opt opt_flags)
{
	struct fw_priv *fw_priv = fw->priv;
	int ret;

	mutex_lock(&fw_lock);
	if (!fw_priv->size || fw_state_is_aborted(fw_priv)) {
		mutex_unlock(&fw_lock);
		return -ENOENT;
	}

	/*
	 * add firmware name into devres list so that we can auto cache
	 * and uncache firmware for device.
	 *
	 * device may has been deleted already, but the problem
	 * should be fixed in devres or driver core.
	 */
	/* don't cache firmware handled without uevent */
	if (device && (opt_flags & FW_OPT_UEVENT) &&
	    !(opt_flags & FW_OPT_NOCACHE)) {
		ret = fw_add_devm_name(device, fw_priv->fw_name);
		if (ret) {
			mutex_unlock(&fw_lock);
			return ret;
		}
	}

	/*
	 * After caching firmware image is started, let it piggyback
	 * on request firmware.
	 */
	if (!(opt_flags & FW_OPT_NOCACHE) &&
	    fw_priv->fwc->state == FW_LOADER_START_CACHE) {
		if (fw_cache_piggyback_on_request(fw_priv->fw_name))
			kref_get(&fw_priv->ref);
	}

	/* pass the pages buffer to driver at the last minute */
	fw_set_page_data(fw_priv, fw);
	mutex_unlock(&fw_lock);
	return 0;
}