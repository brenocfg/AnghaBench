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
struct mfi_softc {int /*<<< orphan*/  mfi_io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mfi_tbolt_sync_map_info (struct mfi_softc*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
mfi_handle_map_sync(void *context, int pending)
{
	struct mfi_softc *sc;

	sc = context;
	mtx_lock(&sc->mfi_io_lock);
	mfi_tbolt_sync_map_info(sc);
	mtx_unlock(&sc->mfi_io_lock);
}