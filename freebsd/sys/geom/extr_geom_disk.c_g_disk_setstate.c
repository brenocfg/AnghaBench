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
struct g_disk_softc {int state; scalar_t__* led; } ;
struct bio {int /*<<< orphan*/  bio_data; } ;

/* Variables and functions */
#define  G_STATE_FAILED 130 
#define  G_STATE_REBUILD 129 
#define  G_STATE_RESYNC 128 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_set (scalar_t__*,char const*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
g_disk_setstate(struct bio *bp, struct g_disk_softc *sc)
{
	const char *cmd;

	memcpy(&sc->state, bp->bio_data, sizeof(sc->state));
	if (sc->led[0] != 0) {
		switch (sc->state) {
		case G_STATE_FAILED:
			cmd = "1";
			break;
		case G_STATE_REBUILD:
			cmd = "f5";
			break;
		case G_STATE_RESYNC:
			cmd = "f1";
			break;
		default:
			cmd = "0";
			break;
		}
		led_set(sc->led, cmd);
	}
	g_io_deliver(bp, 0);
}