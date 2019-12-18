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
struct bwi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bwi_stop (struct bwi_softc*,int) ; 

int
bwi_shutdown(struct bwi_softc *sc)
{
	bwi_stop(sc, 1);
	return 0;
}