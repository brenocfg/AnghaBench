#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* fc; } ;
struct dcons_crom_softc {TYPE_1__ fd; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* poll ) (TYPE_2__*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int) ; 

__attribute__((used)) static void
dcons_crom_poll(void *p, int arg)
{
	struct dcons_crom_softc *sc = (struct dcons_crom_softc *) p;

	sc->fd.fc->poll(sc->fd.fc, -1, -1);
}