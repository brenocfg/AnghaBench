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
struct rtwn_softc {int mac_size; TYPE_1__* mac_prog; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int rtwn_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rtwn_mac_init(struct rtwn_softc *sc)
{
	int i, error;

	/* Write MAC initialization values. */
	for (i = 0; i < sc->mac_size; i++) {
		error = rtwn_write_1(sc, sc->mac_prog[i].reg,
		    sc->mac_prog[i].val);
		if (error != 0)
			return (error);
	}

	return (0);
}