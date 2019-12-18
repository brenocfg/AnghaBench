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
struct drm_connector {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ connector_status_connected ; 
 scalar_t__ connector_status_disconnected ; 

__attribute__((used)) static bool drm_connector_enabled(struct drm_connector *connector, bool strict)
{
	bool enable;

	if (strict)
		enable = connector->status == connector_status_connected;
	else
		enable = connector->status != connector_status_disconnected;

	return enable;
}