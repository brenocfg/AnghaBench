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
struct drm_mode_object {int dummy; } ;
struct drm_mode_get_encoder {int /*<<< orphan*/  possible_clones; int /*<<< orphan*/  possible_crtcs; int /*<<< orphan*/  encoder_id; int /*<<< orphan*/  encoder_type; scalar_t__ crtc_id; } ;
struct drm_file {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct drm_encoder {int /*<<< orphan*/  possible_clones; int /*<<< orphan*/  possible_crtcs; TYPE_3__ base; int /*<<< orphan*/  encoder_type; TYPE_2__* crtc; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; } ;
struct drm_device {TYPE_4__ mode_config; } ;
struct TYPE_5__ {scalar_t__ id; } ;
struct TYPE_6__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_MODE_OBJECT_ENCODER ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct drm_mode_object* drm_mode_object_find (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_encoder* obj_to_encoder (struct drm_mode_object*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int drm_mode_getencoder(struct drm_device *dev, void *data,
			struct drm_file *file_priv)
{
	struct drm_mode_get_encoder *enc_resp = data;
	struct drm_mode_object *obj;
	struct drm_encoder *encoder;
	int ret = 0;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return -EINVAL;

	sx_xlock(&dev->mode_config.mutex);
	obj = drm_mode_object_find(dev, enc_resp->encoder_id,
				   DRM_MODE_OBJECT_ENCODER);
	if (!obj) {
		ret = -EINVAL;
		goto out;
	}
	encoder = obj_to_encoder(obj);

	if (encoder->crtc)
		enc_resp->crtc_id = encoder->crtc->base.id;
	else
		enc_resp->crtc_id = 0;
	enc_resp->encoder_type = encoder->encoder_type;
	enc_resp->encoder_id = encoder->base.id;
	enc_resp->possible_crtcs = encoder->possible_crtcs;
	enc_resp->possible_clones = encoder->possible_clones;

out:
	sx_xunlock(&dev->mode_config.mutex);
	return ret;
}