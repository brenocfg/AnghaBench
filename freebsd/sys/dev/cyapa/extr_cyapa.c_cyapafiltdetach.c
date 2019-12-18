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
struct knote {scalar_t__ kn_hook; } ;
struct knlist {int dummy; } ;
struct TYPE_2__ {struct knlist si_note; } ;
struct cyapa_softc {TYPE_1__ selinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_remove (struct knlist*,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cyapafiltdetach(struct knote *kn)
{
	struct cyapa_softc *sc;
	struct knlist *knlist;

	sc = (struct cyapa_softc *)kn->kn_hook;

	knlist = &sc->selinfo.si_note;
	knlist_remove(knlist, kn, 0);
}