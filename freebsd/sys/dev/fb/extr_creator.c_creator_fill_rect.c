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
struct creator_softc {int dummy; } ;

/* Variables and functions */
 int FBC_DRAWOP_RECTANGLE ; 
 int FBC_ROP_NEW ; 
 int /*<<< orphan*/  FFB_FBC ; 
 int /*<<< orphan*/  FFB_FBC_BH ; 
 int /*<<< orphan*/  FFB_FBC_BW ; 
 int /*<<< orphan*/  FFB_FBC_BX ; 
 int /*<<< orphan*/  FFB_FBC_BY ; 
 int /*<<< orphan*/  FFB_FBC_DRAWOP ; 
 int /*<<< orphan*/  FFB_FBC_ROP ; 
 int /*<<< orphan*/  FFB_WRITE (struct creator_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * creator_cmap ; 
 int /*<<< orphan*/  creator_ras_fifo_wait (struct creator_softc*,int) ; 
 int /*<<< orphan*/  creator_ras_setfg (struct creator_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  creator_ras_setpmask (struct creator_softc*,int) ; 
 int /*<<< orphan*/  creator_ras_wait (struct creator_softc*) ; 

__attribute__((used)) static int
creator_fill_rect(video_adapter_t *adp, int val, int x, int y, int cx, int cy)
{
	struct creator_softc *sc;

	sc = (struct creator_softc *)adp;
	creator_ras_setpmask(sc, 0xffffffff);
	creator_ras_fifo_wait(sc, 2);
	FFB_WRITE(sc, FFB_FBC, FFB_FBC_ROP, FBC_ROP_NEW);
	FFB_WRITE(sc, FFB_FBC, FFB_FBC_DRAWOP, FBC_DRAWOP_RECTANGLE);
	creator_ras_setfg(sc, creator_cmap[val & 0xf]);
	/*
	 * Note that at least the Elite3D cards are sensitive to the order
	 * of operations here.
	 */
	creator_ras_fifo_wait(sc, 4);
	FFB_WRITE(sc, FFB_FBC, FFB_FBC_BY, y);
	FFB_WRITE(sc, FFB_FBC, FFB_FBC_BX, x);
	FFB_WRITE(sc, FFB_FBC, FFB_FBC_BH, cy);
	FFB_WRITE(sc, FFB_FBC, FFB_FBC_BW, cx);
	creator_ras_wait(sc);
	return (0);
}