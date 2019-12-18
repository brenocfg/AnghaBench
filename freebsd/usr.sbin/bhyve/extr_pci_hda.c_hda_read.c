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
typedef  scalar_t__ uint32_t ;
struct hda_softc {int wall_clock_start; } ;

/* Variables and functions */
 scalar_t__ HDAC_WALCLK ; 
 int hda_get_clock_ns () ; 
 scalar_t__ hda_get_reg_by_offset (struct hda_softc*,scalar_t__) ; 

__attribute__((used)) static uint32_t
hda_read(struct hda_softc *sc, uint32_t offset)
{
	if (offset == HDAC_WALCLK)
		return (24 * (hda_get_clock_ns() -			\
			sc->wall_clock_start) / 1000);

	return (hda_get_reg_by_offset(sc, offset));
}