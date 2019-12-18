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
typedef  int uint16_t ;
struct nvbl_softc {int /*<<< orphan*/  sc_memr; } ;

/* Variables and functions */
 int NVIDIA_BRIGHT_MIN ; 
 int NVIDIA_BRIGHT_SCALE ; 
 int /*<<< orphan*/  NVIDIA_PMC_OFF ; 
 int bus_read_stream_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvbl_getlevel(struct nvbl_softc *sc)
{
	uint16_t level;

	level = bus_read_stream_2(sc->sc_memr, NVIDIA_PMC_OFF) & 0x7fff;

	if (level  < NVIDIA_BRIGHT_MIN)
		return 0;

	level = (level - NVIDIA_BRIGHT_MIN) / NVIDIA_BRIGHT_SCALE;

	return (level);
}