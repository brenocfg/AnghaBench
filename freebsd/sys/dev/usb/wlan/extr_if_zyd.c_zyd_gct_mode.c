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
struct zyd_softc {int dummy; } ;
struct zyd_rf {struct zyd_softc* rf_sc; } ;

/* Variables and functions */
 int nitems (int const*) ; 
 int zyd_rfwrite (struct zyd_softc*,int const) ; 

__attribute__((used)) static int
zyd_gct_mode(struct zyd_rf *rf)
{
	struct zyd_softc *sc = rf->rf_sc;
	static const uint32_t mode[] = {
		0x25f98, 0x25f9a, 0x25f94, 0x27fd4
	};
	int i, error;

	for (i = 0; i < nitems(mode); i++) {
		if ((error = zyd_rfwrite(sc, mode[i])) != 0)
			break;
	}
	return (error);
}