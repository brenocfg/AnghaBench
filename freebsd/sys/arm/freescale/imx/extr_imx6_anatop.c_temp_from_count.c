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
struct imx6_anatop_softc {int temp_high_val; int temp_high_cnt; int temp_room_cnt; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
temp_from_count(struct imx6_anatop_softc *sc, uint32_t count)
{

	return (((sc->temp_high_val - (count - sc->temp_high_cnt) *
	    (sc->temp_high_val - 250) / 
	    (sc->temp_room_cnt - sc->temp_high_cnt))));
}