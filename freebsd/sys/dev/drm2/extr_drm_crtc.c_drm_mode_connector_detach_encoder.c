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
struct TYPE_2__ {scalar_t__ id; } ;
struct drm_encoder {TYPE_1__ base; } ;
struct drm_connector {scalar_t__* encoder_ids; struct drm_encoder* encoder; } ;

/* Variables and functions */
 int DRM_CONNECTOR_MAX_ENCODER ; 

void drm_mode_connector_detach_encoder(struct drm_connector *connector,
				    struct drm_encoder *encoder)
{
	int i;
	for (i = 0; i < DRM_CONNECTOR_MAX_ENCODER; i++) {
		if (connector->encoder_ids[i] == encoder->base.id) {
			connector->encoder_ids[i] = 0;
			if (connector->encoder == encoder)
				connector->encoder = NULL;
			break;
		}
	}
}