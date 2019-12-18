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
struct dc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BASE_COLOR_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_DISP_DISP_COLOR_CONTROL ; 
 int /*<<< orphan*/  DC_DISP_DISP_SIGNAL_OPTIONS0 ; 
 int /*<<< orphan*/  DC_DISP_DISP_TIMING_OPTIONS ; 
 int /*<<< orphan*/  DC_DISP_H_PULSE2_CONTROL ; 
 int /*<<< orphan*/  DC_DISP_H_PULSE2_POSITION_A ; 
 int DITHER_CONTROL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DITHER_DISABLE ; 
 int H_PULSE2_ENABLE ; 
 int /*<<< orphan*/  LAST_END_A ; 
 int PULSE_CONTROL_LAST (int /*<<< orphan*/ ) ; 
 int PULSE_CONTROL_QUAL (int /*<<< orphan*/ ) ; 
 int PULSE_END (int) ; 
 int PULSE_START (int) ; 
 int /*<<< orphan*/  QUAL_VACTIVE ; 
 int /*<<< orphan*/  SIZE_BASE888 ; 
 int VSYNC_H_POSITION (int) ; 
 int /*<<< orphan*/  WR4 (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 struct dc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dc_setup_timing(device_t dev, int h_pulse_start)
{
	struct dc_softc *sc;

	sc = device_get_softc(dev);

	/* Setup display timing */
	WR4(sc, DC_DISP_DISP_TIMING_OPTIONS, VSYNC_H_POSITION(1));
	WR4(sc, DC_DISP_DISP_COLOR_CONTROL,
	    DITHER_CONTROL(DITHER_DISABLE) | BASE_COLOR_SIZE(SIZE_BASE888));

	WR4(sc, DC_DISP_DISP_SIGNAL_OPTIONS0, H_PULSE2_ENABLE);
	WR4(sc, DC_DISP_H_PULSE2_CONTROL,
	    PULSE_CONTROL_QUAL(QUAL_VACTIVE) | PULSE_CONTROL_LAST(LAST_END_A));

	WR4(sc, DC_DISP_H_PULSE2_POSITION_A,
	    PULSE_START(h_pulse_start) | PULSE_END(h_pulse_start + 8));
}