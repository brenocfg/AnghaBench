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
struct am7990_softc {int /*<<< orphan*/  lsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  lance_detach (int /*<<< orphan*/ *) ; 

void
am7990_detach(struct am7990_softc *sc)
{

	lance_detach(&sc->lsc);
}