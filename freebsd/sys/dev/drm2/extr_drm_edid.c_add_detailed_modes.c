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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct edid {int features; } ;
struct drm_connector {int dummy; } ;
struct detailed_mode_closure {int member_2; int preferred; int modes; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; struct edid* member_1; struct drm_connector* member_0; } ;

/* Variables and functions */
 int DRM_EDID_FEATURE_PREFERRED_TIMING ; 
 int /*<<< orphan*/  do_detailed_mode ; 
 int /*<<< orphan*/  drm_for_each_detailed_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct detailed_mode_closure*) ; 
 int /*<<< orphan*/  version_greater (struct edid*,int,int) ; 

__attribute__((used)) static int
add_detailed_modes(struct drm_connector *connector, struct edid *edid,
		   u32 quirks)
{
	struct detailed_mode_closure closure = {
		connector,
		edid,
		1,
		quirks,
		0
	};

	if (closure.preferred && !version_greater(edid, 1, 3))
		closure.preferred =
		    (edid->features & DRM_EDID_FEATURE_PREFERRED_TIMING);

	drm_for_each_detailed_block((u8 *)edid, do_detailed_mode, &closure);

	return closure.modes;
}