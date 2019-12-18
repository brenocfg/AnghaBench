#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
struct TYPE_4__ {int vi_width; } ;
struct TYPE_5__ {TYPE_1__ va_info; } ;
typedef  TYPE_2__ video_adapter_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_int ;
struct terasic_mtl_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  terasic_mtl_text_putc (struct terasic_mtl_softc*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
terasic_mtl_vidsw_putc(video_adapter_t *adp, vm_offset_t off, uint8_t c,
    uint8_t a)
{
	struct terasic_mtl_softc *sc;
	u_int col, row;

	sc = (struct terasic_mtl_softc *)adp;
	col = (off % adp->va_info.vi_width);
	row = (off / adp->va_info.vi_width);
	terasic_mtl_text_putc(sc, col, row, c, a);
	return (0);
}