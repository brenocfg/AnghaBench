#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  va_flags; } ;
typedef  TYPE_1__ video_adapter_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  V_ADP_INITIALIZED ; 
 int /*<<< orphan*/  V_ADP_REGISTERED ; 
 int biosadapters ; 
 int /*<<< orphan*/  config_done (TYPE_1__*) ; 
 int /*<<< orphan*/  init_done (TYPE_1__*) ; 
 int /*<<< orphan*/  probe_done (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_sub_configure (int /*<<< orphan*/ ) ; 
 scalar_t__ vid_register (TYPE_1__*) ; 

__attribute__((used)) static int
vga_init(int unit, video_adapter_t *adp, int flags)
{
    if ((unit >= biosadapters) || (adp == NULL) || !probe_done(adp))
	return ENXIO;

    if (!init_done(adp)) {
	/* nothing to do really... */
	adp->va_flags |= V_ADP_INITIALIZED;
    }

    if (!config_done(adp)) {
	if (vid_register(adp) < 0)
		return ENXIO;
	adp->va_flags |= V_ADP_REGISTERED;
    }
    if (vga_sub_configure != NULL)
	(*vga_sub_configure)(0);

    return 0;
}