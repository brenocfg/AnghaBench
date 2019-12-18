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
typedef  int u8 ;
struct drm_display_mode {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 struct drm_display_mode* drm_mode_duplicate (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int drm_num_cea_modes ; 
 int /*<<< orphan*/ * edid_cea_modes ; 

__attribute__((used)) static int
do_cea_modes (struct drm_connector *connector, u8 *db, u8 len)
{
	struct drm_device *dev = connector->dev;
	u8 * mode, cea_mode;
	int modes = 0;

	for (mode = db; mode < db + len; mode++) {
		cea_mode = (*mode & 127) - 1; /* CEA modes are numbered 1..127 */
		if (cea_mode < drm_num_cea_modes) {
			struct drm_display_mode *newmode;
			newmode = drm_mode_duplicate(dev,
						     &edid_cea_modes[cea_mode]);
			if (newmode) {
				drm_mode_probed_add(connector, newmode);
				modes++;
			}
		}
	}

	return modes;
}