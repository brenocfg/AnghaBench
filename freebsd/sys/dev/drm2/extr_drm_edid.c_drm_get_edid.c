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
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ drm_do_get_edid (struct drm_connector*,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_probe_ddc (int /*<<< orphan*/ ) ; 

struct edid *drm_get_edid(struct drm_connector *connector,
			  device_t adapter)
{
	struct edid *edid = NULL;

	if (drm_probe_ddc(adapter))
		edid = (struct edid *)drm_do_get_edid(connector, adapter);

	return edid;
}