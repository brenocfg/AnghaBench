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
struct TYPE_2__ {int va_flags; size_t va_index; int /*<<< orphan*/  va_mode; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ VESA_MODE (int /*<<< orphan*/ ) ; 
 int V_ADP_DAC8 ; 
 int V_ADP_VESA ; 
 int /*<<< orphan*/  prevvidsw ; 
 TYPE_1__* vesa_adp ; 
 int /*<<< orphan*/  vesa_bios_set_dac (int) ; 
 int /*<<< orphan*/  vesa_bios_uninit () ; 
 int vesa_unload_ioctl () ; 
 int /*<<< orphan*/ * vidsw ; 

__attribute__((used)) static int
vesa_unload(void)
{
	int error;

	/* The driver never initialized, so make it easy to unload. */
	if (vesa_adp == NULL)
		return (0);

	/* if the adapter is currently in a VESA mode, don't unload */
	if (VESA_MODE(vesa_adp->va_mode))
		return (EBUSY);
	/* 
	 * FIXME: if there is at least one vty which is in a VESA mode,
	 * we shouldn't be unloading! XXX
	 */

	if ((error = vesa_unload_ioctl()) == 0) {
		if (vesa_adp != NULL) {
			if ((vesa_adp->va_flags & V_ADP_DAC8) != 0) {
				vesa_bios_set_dac(6);
				vesa_adp->va_flags &= ~V_ADP_DAC8;
			}
			vesa_adp->va_flags &= ~V_ADP_VESA;
			vidsw[vesa_adp->va_index] = prevvidsw;
		}
	}

	vesa_bios_uninit();

	return (error);
}