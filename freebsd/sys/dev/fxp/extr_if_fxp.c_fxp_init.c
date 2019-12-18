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
struct fxp_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FXP_LOCK (struct fxp_softc*) ; 
 int /*<<< orphan*/  FXP_UNLOCK (struct fxp_softc*) ; 
 int /*<<< orphan*/  fxp_init_body (struct fxp_softc*,int) ; 

__attribute__((used)) static void
fxp_init(void *xsc)
{
	struct fxp_softc *sc = xsc;

	FXP_LOCK(sc);
	fxp_init_body(sc, 1);
	FXP_UNLOCK(sc);
}