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
struct videomode {int dot_clock; scalar_t__ hdisplay; scalar_t__ vdisplay; int /*<<< orphan*/  vtotal; int /*<<< orphan*/  htotal; } ;
struct edid_info {int edid_nmodes; struct videomode* edid_modes; } ;

/* Variables and functions */
 int DIVIDE (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct videomode *
edid_search_mode(struct edid_info *edid, const struct videomode *mode)
{
	int	refresh, i;

	refresh = DIVIDE(DIVIDE(mode->dot_clock * 1000,
	    mode->htotal), mode->vtotal);
	for (i = 0; i < edid->edid_nmodes; i++) {
		if (mode->hdisplay == edid->edid_modes[i].hdisplay &&
		    mode->vdisplay == edid->edid_modes[i].vdisplay &&
		    refresh == DIVIDE(DIVIDE(
		    edid->edid_modes[i].dot_clock * 1000,
		    edid->edid_modes[i].htotal), edid->edid_modes[i].vtotal)) {
			return &edid->edid_modes[i];
		}
	}
	return NULL;
}