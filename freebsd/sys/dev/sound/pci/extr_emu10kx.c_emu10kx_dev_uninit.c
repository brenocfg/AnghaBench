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
struct emu_sc_info {int /*<<< orphan*/  emu10kx_lock; int /*<<< orphan*/ * cdev; scalar_t__ emu10kx_isopen; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
emu10kx_dev_uninit(struct emu_sc_info *sc)
{
	mtx_lock(&sc->emu10kx_lock);
	if (sc->emu10kx_isopen) {
		mtx_unlock(&sc->emu10kx_lock);
		return (EBUSY);
	}
	if (sc->cdev)
		destroy_dev(sc->cdev);
	sc->cdev = NULL;

	mtx_destroy(&sc->emu10kx_lock);
	return (0);
}