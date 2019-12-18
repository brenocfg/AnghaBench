#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct drm_display_mode {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;
struct TYPE_4__ {struct cvt_timing* cvt; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
struct TYPE_6__ {TYPE_2__ other_data; } ;
struct detailed_timing {TYPE_3__ data; } ;
struct cvt_timing {int* code; } ;

/* Variables and functions */
 struct drm_display_mode* drm_cvt_mode (struct drm_device*,int,int,int const,int,int,int) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  memcmp (int*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int drm_cvt_modes(struct drm_connector *connector,
			 struct detailed_timing *timing)
{
	int i, j, modes = 0;
	struct drm_display_mode *newmode;
	struct drm_device *dev = connector->dev;
	struct cvt_timing *cvt;
	const int rates[] = { 60, 85, 75, 60, 50 };
	const u8 empty[3] = { 0, 0, 0 };

	for (i = 0; i < 4; i++) {
		int width = 0, height;
		cvt = &(timing->data.other_data.data.cvt[i]);

		if (!memcmp(cvt->code, empty, 3))
			continue;

		height = (cvt->code[0] + ((cvt->code[1] & 0xf0) << 4) + 1) * 2;
		switch (cvt->code[1] & 0x0c) {
		case 0x00:
			width = height * 4 / 3;
			break;
		case 0x04:
			width = height * 16 / 9;
			break;
		case 0x08:
			width = height * 16 / 10;
			break;
		case 0x0c:
			width = height * 15 / 9;
			break;
		}

		for (j = 1; j < 5; j++) {
			if (cvt->code[2] & (1 << j)) {
				newmode = drm_cvt_mode(dev, width, height,
						       rates[j], j == 0,
						       false, false);
				if (newmode) {
					drm_mode_probed_add(connector, newmode);
					modes++;
				}
			}
		}
	}

	return modes;
}