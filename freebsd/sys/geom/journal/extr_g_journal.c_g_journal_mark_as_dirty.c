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
struct g_journal_softc {int /*<<< orphan*/  sc_dconsumer; int /*<<< orphan*/  sc_name; } ;
struct g_journal_desc {int /*<<< orphan*/  (* jd_dirty ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GJ_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 struct g_journal_desc** g_journal_filesystems ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_journal_mark_as_dirty(struct g_journal_softc *sc)
{
	const struct g_journal_desc *desc;
	int i;

	GJ_DEBUG(1, "Marking file system %s as dirty.", sc->sc_name);
	for (i = 0; (desc = g_journal_filesystems[i]) != NULL; i++)
		desc->jd_dirty(sc->sc_dconsumer);
}