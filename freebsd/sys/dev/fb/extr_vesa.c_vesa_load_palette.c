#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int va_flags; int /*<<< orphan*/  va_mode; } ;
typedef  TYPE_1__ video_adapter_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {int (* load_palette ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ VESA_MODE (int /*<<< orphan*/ ) ; 
 int V_ADP_DAC8 ; 
 TYPE_5__* prevvidsw ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* vesa_adp ; 
 scalar_t__ vesa_bios_load_palette (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
vesa_load_palette(video_adapter_t *adp, u_char *palette)
{
	int bits;

	if (adp == vesa_adp && VESA_MODE(adp->va_mode)) {
		bits = (adp->va_flags & V_ADP_DAC8) != 0 ? 8 : 6;
		if (vesa_bios_load_palette(0, 256, palette, bits) == 0)
			return (0);
	}

	return ((*prevvidsw->load_palette)(adp, palette));
}