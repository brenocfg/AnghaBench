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
struct bxe_softc {int /*<<< orphan*/ * fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int bxe_setup_queue (struct bxe_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_setup_leading(struct bxe_softc *sc)
{
    return (bxe_setup_queue(sc, &sc->fp[0], TRUE));
}