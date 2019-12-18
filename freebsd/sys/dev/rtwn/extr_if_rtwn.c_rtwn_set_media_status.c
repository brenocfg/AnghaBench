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
union sec_param {int /*<<< orphan*/  macid; } ;
struct rtwn_softc {int /*<<< orphan*/  (* sc_set_media_status ) (struct rtwn_softc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rtwn_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rtwn_set_media_status(struct rtwn_softc *sc, union sec_param *data)
{
	sc->sc_set_media_status(sc, data->macid);
}