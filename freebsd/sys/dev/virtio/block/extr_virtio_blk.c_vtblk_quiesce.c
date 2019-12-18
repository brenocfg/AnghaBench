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
struct vtblk_softc {int /*<<< orphan*/  vtblk_vq; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  VTBLK_LOCK_ASSERT (struct vtblk_softc*) ; 
 int /*<<< orphan*/  VTBLK_MTX (struct vtblk_softc*) ; 
 int /*<<< orphan*/  VTBLK_QUIESCE_TIMEOUT ; 
 scalar_t__ mtx_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtblk_quiesce(struct vtblk_softc *sc)
{
	int error;

	VTBLK_LOCK_ASSERT(sc);
	error = 0;

	while (!virtqueue_empty(sc->vtblk_vq)) {
		if (mtx_sleep(&sc->vtblk_vq, VTBLK_MTX(sc), PRIBIO, "vtblkq",
		    VTBLK_QUIESCE_TIMEOUT) == EWOULDBLOCK) {
			error = EBUSY;
			break;
		}
	}

	return (error);
}