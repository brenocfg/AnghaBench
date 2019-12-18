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
struct TYPE_2__ {scalar_t__ num_encoder; scalar_t__ num_crtc; scalar_t__ num_connector; scalar_t__ num_fb; int /*<<< orphan*/  mutex; int /*<<< orphan*/  crtc_names; int /*<<< orphan*/  plane_list; int /*<<< orphan*/  property_blob_list; int /*<<< orphan*/  property_list; int /*<<< orphan*/  encoder_list; int /*<<< orphan*/  connector_list; int /*<<< orphan*/  crtc_list; int /*<<< orphan*/  fb_list; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_names_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_create_standard_connector_properties (struct drm_device*) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

void drm_mode_config_init(struct drm_device *dev)
{
	sx_init(&dev->mode_config.mutex, "kmslk");
	INIT_LIST_HEAD(&dev->mode_config.fb_list);
	INIT_LIST_HEAD(&dev->mode_config.crtc_list);
	INIT_LIST_HEAD(&dev->mode_config.connector_list);
	INIT_LIST_HEAD(&dev->mode_config.encoder_list);
	INIT_LIST_HEAD(&dev->mode_config.property_list);
	INIT_LIST_HEAD(&dev->mode_config.property_blob_list);
	INIT_LIST_HEAD(&dev->mode_config.plane_list);
	drm_gem_names_init(&dev->mode_config.crtc_names);

	sx_xlock(&dev->mode_config.mutex);
	drm_mode_create_standard_connector_properties(dev);
	sx_xunlock(&dev->mode_config.mutex);

	/* Just to be sure */
	dev->mode_config.num_fb = 0;
	dev->mode_config.num_connector = 0;
	dev->mode_config.num_crtc = 0;
	dev->mode_config.num_encoder = 0;
}