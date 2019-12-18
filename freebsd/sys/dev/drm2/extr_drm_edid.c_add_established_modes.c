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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int t1; int t2; int mfg_rsvd; } ;
struct edid {TYPE_1__ established_timings; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;
struct detailed_mode_closure {int modes; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; struct edid* member_1; struct drm_connector* member_0; } ;

/* Variables and functions */
 int EDID_EST_TIMINGS ; 
 int /*<<< orphan*/  do_established_modes ; 
 int /*<<< orphan*/  drm_for_each_detailed_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct detailed_mode_closure*) ; 
 struct drm_display_mode* drm_mode_duplicate (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/ * edid_est_modes ; 
 scalar_t__ version_greater (struct edid*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
add_established_modes(struct drm_connector *connector, struct edid *edid)
{
	struct drm_device *dev = connector->dev;
	unsigned long est_bits = edid->established_timings.t1 |
		(edid->established_timings.t2 << 8) |
		((edid->established_timings.mfg_rsvd & 0x80) << 9);
	int i, modes = 0;
	struct detailed_mode_closure closure = {
		connector, edid, 0, 0, 0
	};

	for (i = 0; i <= EDID_EST_TIMINGS; i++) {
		if (est_bits & (1<<i)) {
			struct drm_display_mode *newmode;
			newmode = drm_mode_duplicate(dev, &edid_est_modes[i]);
			if (newmode) {
				drm_mode_probed_add(connector, newmode);
				modes++;
			}
		}
	}

	if (version_greater(edid, 1, 0))
		    drm_for_each_detailed_block((u8 *)edid,
						do_established_modes, &closure);

	return modes + closure.modes;
}