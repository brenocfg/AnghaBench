#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct siosc {int /*<<< orphan*/  io_port; int /*<<< orphan*/  io_res; TYPE_1__* methods; int /*<<< orphan*/  conf_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enter ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sio_conf_enter(struct siosc *sc)
{
	mtx_lock(&sc->conf_lock);
	sc->methods->enter(sc->io_res, sc->io_port);
}