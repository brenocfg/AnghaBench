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
struct creator_softc {int sc_flags; } ;

/* Variables and functions */
 int CREATOR_CURINV ; 
 int /*<<< orphan*/  FFB_DAC ; 
 int FFB_DAC_CUR_CTRL ; 
 int FFB_DAC_CUR_CTRL_P0 ; 
 int FFB_DAC_CUR_CTRL_P1 ; 
 int /*<<< orphan*/  FFB_DAC_TYPE2 ; 
 int /*<<< orphan*/  FFB_DAC_VALUE2 ; 
 int /*<<< orphan*/  FFB_WRITE (struct creator_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
creator_cursor_enable(struct creator_softc *sc, int onoff)
{
	int v;

	FFB_WRITE(sc, FFB_DAC, FFB_DAC_TYPE2, FFB_DAC_CUR_CTRL);
	if (sc->sc_flags & CREATOR_CURINV)
		v = onoff ? FFB_DAC_CUR_CTRL_P0 | FFB_DAC_CUR_CTRL_P1 : 0;
	else
		v = onoff ? 0 : FFB_DAC_CUR_CTRL_P0 | FFB_DAC_CUR_CTRL_P1;
	FFB_WRITE(sc, FFB_DAC, FFB_DAC_VALUE2, v);
}