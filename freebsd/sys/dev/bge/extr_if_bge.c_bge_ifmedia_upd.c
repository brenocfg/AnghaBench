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
struct bge_softc {int dummy; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_LOCK (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_UNLOCK (struct bge_softc*) ; 
 int bge_ifmedia_upd_locked (int /*<<< orphan*/ ) ; 
 struct bge_softc* if_getsoftc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bge_ifmedia_upd(if_t ifp)
{
	struct bge_softc *sc = if_getsoftc(ifp);
	int res;

	BGE_LOCK(sc);
	res = bge_ifmedia_upd_locked(ifp);
	BGE_UNLOCK(sc);

	return (res);
}