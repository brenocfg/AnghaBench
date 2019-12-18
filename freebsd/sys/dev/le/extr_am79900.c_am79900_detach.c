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
struct am79900_softc {int /*<<< orphan*/  lsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  lance_detach (int /*<<< orphan*/ *) ; 

void
am79900_detach(struct am79900_softc *sc)
{

	lance_detach(&sc->lsc);
}