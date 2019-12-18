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
struct mtkswitch_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK (struct mtkswitch_softc*) ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK_ASSERT (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ MTKSWITCH_READ (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_STRT ; 
 int /*<<< orphan*/  MTKSWITCH_UNLOCK (struct mtkswitch_softc*) ; 
 int /*<<< orphan*/  MTKSWITCH_WRITE (struct mtkswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRT_RESET ; 

__attribute__((used)) static int
mtkswitch_reset(struct mtkswitch_softc *sc)
{

	MTKSWITCH_LOCK_ASSERT(sc, MA_NOTOWNED);
	MTKSWITCH_LOCK(sc);
	MTKSWITCH_WRITE(sc, MTKSWITCH_STRT, STRT_RESET);
	while (MTKSWITCH_READ(sc, MTKSWITCH_STRT) != 0);
	MTKSWITCH_UNLOCK(sc);

	return (0);
}