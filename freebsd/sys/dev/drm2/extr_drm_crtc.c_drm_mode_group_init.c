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
typedef  int uint32_t ;
struct drm_mode_group {scalar_t__ num_encoders; scalar_t__ num_connectors; scalar_t__ num_crtcs; int /*<<< orphan*/  id_list; } ;
struct TYPE_2__ {scalar_t__ num_encoder; scalar_t__ num_connector; scalar_t__ num_crtc; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MEM_KMS ; 
 int ENOMEM ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 

int drm_mode_group_init(struct drm_device *dev, struct drm_mode_group *group)
{
	uint32_t total_objects = 0;

	total_objects += dev->mode_config.num_crtc;
	total_objects += dev->mode_config.num_connector;
	total_objects += dev->mode_config.num_encoder;

	group->id_list = malloc(total_objects * sizeof(uint32_t),
	    DRM_MEM_KMS, M_WAITOK | M_ZERO);
	if (!group->id_list)
		return -ENOMEM;

	group->num_crtcs = 0;
	group->num_connectors = 0;
	group->num_encoders = 0;
	return 0;
}