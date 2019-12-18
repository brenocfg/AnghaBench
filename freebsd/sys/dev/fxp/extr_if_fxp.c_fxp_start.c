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
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  FXP_LOCK (struct fxp_softc*) ; 
 int /*<<< orphan*/  FXP_UNLOCK (struct fxp_softc*) ; 
 int /*<<< orphan*/  fxp_start_body (int /*<<< orphan*/ ) ; 
 struct fxp_softc* if_getsoftc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fxp_start(if_t ifp)
{
	struct fxp_softc *sc = if_getsoftc(ifp);

	FXP_LOCK(sc);
	fxp_start_body(ifp);
	FXP_UNLOCK(sc);
}