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
struct ow_temp_softc {int flags; scalar_t__ type; int temp; int reading_interval; int /*<<< orphan*/  temp_lock; int /*<<< orphan*/  bad_reads; int /*<<< orphan*/  bad_crc; int /*<<< orphan*/  dev; scalar_t__ parasite; } ;
typedef  int /*<<< orphan*/  scratch ;
typedef  int int16_t ;

/* Variables and functions */
 scalar_t__ OWT_DS1820 ; 
 int OW_TEMP_DONE ; 
 int OW_TEMP_RUNNING ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (struct ow_temp_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ow_temp_convert_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ow_temp_read_power_supply (int /*<<< orphan*/ ,scalar_t__*) ; 
 int ow_temp_read_scratchpad (int /*<<< orphan*/ ,int*,int) ; 
 int own_crc (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pause (char*,int) ; 

__attribute__((used)) static void
ow_temp_event_thread(void *arg)
{
	struct ow_temp_softc *sc;
	uint8_t scratch[8 + 1];
	uint8_t crc;
	int retries, rv, tmp;

	sc = arg;
	pause("owtstart", device_get_unit(sc->dev) * hz / 100);	// 10ms stagger
	mtx_lock(&sc->temp_lock);
	sc->flags |= OW_TEMP_RUNNING;
	mtx_unlock(&sc->temp_lock);
	ow_temp_read_power_supply(sc->dev, &sc->parasite);
	if (sc->parasite)
		device_printf(sc->dev, "Running in parasitic mode unsupported\n");
	mtx_lock(&sc->temp_lock);
	while ((sc->flags & OW_TEMP_DONE) == 0) {
		mtx_unlock(&sc->temp_lock);
		ow_temp_convert_t(sc->dev);
		mtx_lock(&sc->temp_lock);
		msleep(sc, &sc->temp_lock, 0, "owtcvt", hz);
		if (sc->flags & OW_TEMP_DONE)
			break;
		mtx_unlock(&sc->temp_lock);
		for (retries = 5; retries > 0; retries--) {
			rv = ow_temp_read_scratchpad(sc->dev, scratch, sizeof(scratch));
			if (rv == 0) {
				crc = own_crc(sc->dev, scratch, sizeof(scratch) - 1);
				if (crc == scratch[8]) {
					if (sc->type == OWT_DS1820) {
						if (scratch[7]) {
							/*
							 * Formula from DS18S20 datasheet, page 6
							 * DS18S20 datasheet says count_per_c is 16, DS1820 does not
							 */
							tmp = (int16_t)((scratch[0] & 0xfe) |
							    (scratch[1] << 8)) << 3;
							tmp += 16 - scratch[6] - 4; /* count_per_c == 16 */
						} else
							tmp = (int16_t)(scratch[0] | (scratch[1] << 8)) << 3;
					} else
						tmp = (int16_t)(scratch[0] | (scratch[1] << 8));
					sc->temp = tmp * 1000 / 16 + 273150;
					break;
				}
				sc->bad_crc++;
			} else
				sc->bad_reads++;
		}
		mtx_lock(&sc->temp_lock);
		msleep(sc, &sc->temp_lock, 0, "owtcvt", sc->reading_interval);
	}
	sc->flags &= ~OW_TEMP_RUNNING;
	mtx_unlock(&sc->temp_lock);
	kproc_exit(0);
}