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
typedef  int uint32_t ;
struct viawd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIAWD_MEM_CTRL ; 
 int VIAWD_MEM_CTRL_ENABLE ; 
 int VIAWD_MEM_CTRL_TRIGGER ; 
 int viawd_read_4 (struct viawd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viawd_write_4 (struct viawd_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
viawd_tmr_state(struct viawd_softc *sc, int enable)
{
	uint32_t reg;

	reg = viawd_read_4(sc, VIAWD_MEM_CTRL);
	if (enable)
		reg |= VIAWD_MEM_CTRL_TRIGGER | VIAWD_MEM_CTRL_ENABLE;
	else
		reg &= ~VIAWD_MEM_CTRL_ENABLE;
	viawd_write_4(sc, VIAWD_MEM_CTRL, reg);
}