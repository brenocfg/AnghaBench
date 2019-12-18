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
typedef  int uint8_t ;
struct rtwn_softc {TYPE_1__** vaps; } ;
struct TYPE_2__ {int curr_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_MSR ; 
 int R92C_MSR_MASK ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
rtwn_set_mode(struct rtwn_softc *sc, uint8_t mode, int id)
{

	rtwn_setbits_1(sc, R92C_MSR, R92C_MSR_MASK << id * 2, mode << id * 2);
	if (sc->vaps[id] != NULL)
		sc->vaps[id]->curr_mode = mode;
}