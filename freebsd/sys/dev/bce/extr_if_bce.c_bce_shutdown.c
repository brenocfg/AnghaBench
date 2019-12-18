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
typedef  int /*<<< orphan*/  u32 ;
struct bce_softc {int bce_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_DRV_MSG_CODE_UNLOAD ; 
 int /*<<< orphan*/  BCE_DRV_MSG_CODE_UNLOAD_LNK_DN ; 
 int /*<<< orphan*/  BCE_LOCK (struct bce_softc*) ; 
 int BCE_NO_WOL_FLAG ; 
 int /*<<< orphan*/  BCE_UNLOCK (struct bce_softc*) ; 
 int /*<<< orphan*/  BCE_VERBOSE ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bce_reset (struct bce_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bce_stop (struct bce_softc*) ; 
 struct bce_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bce_shutdown(device_t dev)
{
	struct bce_softc *sc = device_get_softc(dev);
	u32 msg;

	DBENTER(BCE_VERBOSE);

	BCE_LOCK(sc);
	bce_stop(sc);
	if (sc->bce_flags & BCE_NO_WOL_FLAG)
		msg = BCE_DRV_MSG_CODE_UNLOAD_LNK_DN;
	else
		msg = BCE_DRV_MSG_CODE_UNLOAD;
	bce_reset(sc, msg);
	BCE_UNLOCK(sc);

	DBEXIT(BCE_VERBOSE);

	return (0);
}