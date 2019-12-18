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
typedef  int /*<<< orphan*/  uint16_t ;
struct altera_sdcard_softc {int /*<<< orphan*/  as_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_SDCARD_OFF_ASR ; 
 int /*<<< orphan*/  bus_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 

uint16_t
altera_sdcard_read_asr(struct altera_sdcard_softc *sc)
{

	return (le16toh(bus_read_2(sc->as_res, ALTERA_SDCARD_OFF_ASR)));
}