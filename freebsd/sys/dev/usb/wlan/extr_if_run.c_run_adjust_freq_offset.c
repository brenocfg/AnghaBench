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
typedef  int uint8_t ;
struct run_softc {int freq; } ;

/* Variables and functions */
 int MIN (int,int) ; 
 int /*<<< orphan*/  run_mcu_cmd (struct run_softc*,int,int) ; 
 int /*<<< orphan*/  run_rt3070_rf_read (struct run_softc*,int,int*) ; 

__attribute__((used)) static void
run_adjust_freq_offset(struct run_softc *sc)
{
	uint8_t rf, tmp;

	run_rt3070_rf_read(sc, 17, &rf);
	tmp = rf;
	rf = (rf & ~0x7f) | (sc->freq & 0x7f);
	rf = MIN(rf, 0x5f);

	if (tmp != rf)
		run_mcu_cmd(sc, 0x74, (tmp << 8 ) | rf);
}