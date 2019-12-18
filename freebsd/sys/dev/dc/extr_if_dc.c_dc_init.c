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
struct dc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOCK (struct dc_softc*) ; 
 int /*<<< orphan*/  DC_UNLOCK (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_init_locked (struct dc_softc*) ; 

__attribute__((used)) static void
dc_init(void *xsc)
{
	struct dc_softc *sc = xsc;

	DC_LOCK(sc);
	dc_init_locked(sc);
	DC_UNLOCK(sc);
}