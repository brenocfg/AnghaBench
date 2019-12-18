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
struct sc_info {int /*<<< orphan*/  lock; int /*<<< orphan*/ * mpu_intr; } ;
struct mpu401 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emu_muninit(struct mpu401 *arg, void *cookie)
{
	struct sc_info *sc = cookie;

	snd_mtxlock(sc->lock);
	sc->mpu_intr = NULL;
	snd_mtxunlock(sc->lock);

	return 0;
}