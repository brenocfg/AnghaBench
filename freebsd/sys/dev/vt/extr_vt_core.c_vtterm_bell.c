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
struct vt_window {struct vt_device* vw_device; } ;
struct vt_device {int vd_flags; } ;
struct terminal {struct vt_window* tm_softc; } ;

/* Variables and functions */
 int VDF_QUIET_BELL ; 
 int /*<<< orphan*/  VT_BELLDURATION ; 
 int VT_BELLPITCH ; 
 int /*<<< orphan*/  sysbeep (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_enable_bell ; 

__attribute__((used)) static void
vtterm_bell(struct terminal *tm)
{
	struct vt_window *vw = tm->tm_softc;
	struct vt_device *vd = vw->vw_device;

	if (!vt_enable_bell)
		return;

	if (vd->vd_flags & VDF_QUIET_BELL)
		return;

	sysbeep(1193182 / VT_BELLPITCH, VT_BELLDURATION);
}