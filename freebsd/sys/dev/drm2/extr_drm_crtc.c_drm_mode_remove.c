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
struct drm_display_mode {int /*<<< orphan*/  head; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_destroy (int /*<<< orphan*/ ,struct drm_display_mode*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void drm_mode_remove(struct drm_connector *connector,
		     struct drm_display_mode *mode)
{
	list_del(&mode->head);
	drm_mode_destroy(connector->dev, mode);
}