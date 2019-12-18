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
struct videomode {double dot_clock; double htotal; double vtotal; int hdisplay; int vdisplay; int hsync_start; int hsync_end; int vsync_start; int vsync_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
print_xf86_mode (struct videomode *vmp)
{
	float	vf, hf;

	hf = 1000.0 * vmp->dot_clock / vmp->htotal;
	vf = 1.0 * hf / vmp->vtotal;

    printf("\n");
    printf("  # %dx%d @ %.2f Hz (GTF) hsync: %.2f kHz; pclk: %.2f MHz\n",
	vmp->hdisplay, vmp->vdisplay, vf, hf, vmp->dot_clock / 1000.0);
    
    printf("  Modeline \"%dx%d_%.2f\"  %.2f"
	"  %d %d %d %d"
	"  %d %d %d %d"
	"  -HSync +Vsync\n\n",
	vmp->hdisplay, vmp->vdisplay, vf, (vmp->dot_clock / 1000.0),
	vmp->hdisplay, vmp->hsync_start, vmp->hsync_end, vmp->htotal,
	vmp->vdisplay, vmp->vsync_start, vmp->vsync_end, vmp->vtotal);
}