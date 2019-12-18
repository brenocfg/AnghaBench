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
struct g_mirror_softc {int sc_flags; int /*<<< orphan*/  sc_ndisks; int /*<<< orphan*/  sc_mediasize; int /*<<< orphan*/  sc_balance; int /*<<< orphan*/  sc_slice; int /*<<< orphan*/  sc_syncid; int /*<<< orphan*/  sc_genid; } ;
struct g_mirror_metadata {int md_mflags; int /*<<< orphan*/  md_all; int /*<<< orphan*/  md_mediasize; int /*<<< orphan*/  md_balance; int /*<<< orphan*/  md_slice; int /*<<< orphan*/  md_syncid; int /*<<< orphan*/  md_genid; } ;

/* Variables and functions */
 int G_MIRROR_DEVICE_FLAG_MASK ; 

__attribute__((used)) static void
g_mirror_reinit_from_metadata(struct g_mirror_softc *sc,
    const struct g_mirror_metadata *md)
{

	sc->sc_genid = md->md_genid;
	sc->sc_syncid = md->md_syncid;

	sc->sc_slice = md->md_slice;
	sc->sc_balance = md->md_balance;
	sc->sc_mediasize = md->md_mediasize;
	sc->sc_ndisks = md->md_all;
	sc->sc_flags &= ~G_MIRROR_DEVICE_FLAG_MASK;
	sc->sc_flags |= (md->md_mflags & G_MIRROR_DEVICE_FLAG_MASK);
}