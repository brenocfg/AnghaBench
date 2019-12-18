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
typedef  int /*<<< orphan*/  video_adapter_t ;
struct terasic_mtl_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  terasic_mtl_reg_blank (struct terasic_mtl_softc*) ; 

__attribute__((used)) static int
terasic_mtl_vidsw_blank_display(video_adapter_t *adp, int mode)
{
	struct terasic_mtl_softc *sc;

	sc = (struct terasic_mtl_softc *)adp;
	terasic_mtl_reg_blank(sc);
	return (0);
}