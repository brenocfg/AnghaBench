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
struct iwi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWI_LOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  IWI_LOCK_DECL ; 
 int /*<<< orphan*/  IWI_UNLOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_scanchan (struct iwi_softc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwi_monitor_scan(void *arg, int npending)
{
	struct iwi_softc *sc = arg;
	IWI_LOCK_DECL;

	IWI_LOCK(sc);
	(void) iwi_scanchan(sc, 2000, 0);
	IWI_UNLOCK(sc);
}