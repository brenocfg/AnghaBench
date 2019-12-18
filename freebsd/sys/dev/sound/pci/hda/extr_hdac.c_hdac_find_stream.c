#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hdac_softc {int num_iss; int num_oss; int num_bss; TYPE_1__* streams; } ;
struct TYPE_2__ {int stream; } ;

/* Variables and functions */

__attribute__((used)) static int
hdac_find_stream(struct hdac_softc *sc, int dir, int stream)
{
	int i, ss;

	ss = -1;
	/* Allocate ISS/OSS first. */
	if (dir == 0) {
		for (i = 0; i < sc->num_iss; i++) {
			if (sc->streams[i].stream == stream) {
				ss = i;
				break;
			}
		}
	} else {
		for (i = 0; i < sc->num_oss; i++) {
			if (sc->streams[i + sc->num_iss].stream == stream) {
				ss = i + sc->num_iss;
				break;
			}
		}
	}
	/* Fallback to BSS. */
	if (ss == -1) {
		for (i = 0; i < sc->num_bss; i++) {
			if (sc->streams[i + sc->num_iss + sc->num_oss].stream
			    == stream) {
				ss = i + sc->num_iss + sc->num_oss;
				break;
			}
		}
	}
	return (ss);
}