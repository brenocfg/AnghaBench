#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nifs; int /*<<< orphan*/  if_id; } ;
typedef  TYPE_1__* POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_32 (scalar_t__*) ; 
 int /*<<< orphan*/  oce_if_del (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
oce_delete_nw_interface(POCE_SOFTC sc)
{
	/* currently only single interface is implmeneted */
	if (sc->nifs > 0) {
		oce_if_del(sc, sc->if_id);
		atomic_dec_32(&sc->nifs);
	}
}