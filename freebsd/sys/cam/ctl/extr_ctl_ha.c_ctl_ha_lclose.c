#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ha_softc {TYPE_1__* ha_lso; } ;
struct TYPE_3__ {int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SO_RCV ; 
 int /*<<< orphan*/  soclose (TYPE_1__*) ; 
 int /*<<< orphan*/  soupcall_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctl_ha_lclose(struct ha_softc *softc)
{

	if (softc->ha_lso) {
		SOCKBUF_LOCK(&softc->ha_lso->so_rcv);
		soupcall_clear(softc->ha_lso, SO_RCV);
		SOCKBUF_UNLOCK(&softc->ha_lso->so_rcv);
		soclose(softc->ha_lso);
		softc->ha_lso = NULL;
	}
}