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
struct imx6_anatop_softc {int temp_last_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX6_ANALOG_TEMPMON_TEMPSENSE0 ; 
 int IMX6_ANALOG_TEMPMON_TEMPSENSE0_TEMP_CNT_MASK ; 
 int IMX6_ANALOG_TEMPMON_TEMPSENSE0_TEMP_CNT_SHIFT ; 
 int IMX6_ANALOG_TEMPMON_TEMPSENSE0_VALID ; 
 int imx6_anatop_read_4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
temp_update_count(struct imx6_anatop_softc *sc)
{
	uint32_t val;

	val = imx6_anatop_read_4(IMX6_ANALOG_TEMPMON_TEMPSENSE0);
	if (!(val & IMX6_ANALOG_TEMPMON_TEMPSENSE0_VALID))
		return;
	sc->temp_last_cnt =
	    (val & IMX6_ANALOG_TEMPMON_TEMPSENSE0_TEMP_CNT_MASK) >>
	    IMX6_ANALOG_TEMPMON_TEMPSENSE0_TEMP_CNT_SHIFT;
}