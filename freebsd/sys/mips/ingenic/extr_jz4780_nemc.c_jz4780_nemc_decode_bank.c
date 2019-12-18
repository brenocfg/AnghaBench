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
typedef  int u_int ;
struct simplebus_softc {int nranges; TYPE_1__* ranges; } ;
struct resource {int dummy; } ;
typedef  scalar_t__ rman_res_t ;
struct TYPE_2__ {scalar_t__ host; scalar_t__ size; int bus; } ;

/* Variables and functions */
 scalar_t__ rman_get_end (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 

__attribute__((used)) static int
jz4780_nemc_decode_bank(struct simplebus_softc *sc, struct resource *r,
    u_int *bank)
{
	rman_res_t start, end;
	int i;

	start = rman_get_start(r);
	end = rman_get_end(r);

	/* Remap through ranges property */
	for (i = 0; i < sc->nranges; i++) {
		if (start >= sc->ranges[i].host && end <
		    sc->ranges[i].host + sc->ranges[i].size) {
			*bank = (sc->ranges[i].bus >> 32);
			return (0);
		}
	}
	return (1);
}