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
struct hn_softc {int hn_flags; int /*<<< orphan*/  hn_ifp; } ;

/* Variables and functions */
 int ENXIO ; 
 int HN_FLAG_SYNTH_ATTACHED ; 
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int /*<<< orphan*/  NDIS_RSS_FLAG_DISABLE ; 
 int /*<<< orphan*/  NDIS_RSS_FLAG_NONE ; 
 scalar_t__ bootverbose ; 
 int hn_rndis_conf_rss (struct hn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
hn_rss_reconfig(struct hn_softc *sc)
{
	int error;

	HN_LOCK_ASSERT(sc);

	if ((sc->hn_flags & HN_FLAG_SYNTH_ATTACHED) == 0)
		return (ENXIO);

	/*
	 * Disable RSS first.
	 *
	 * NOTE:
	 * Direct reconfiguration by setting the UNCHG flags does
	 * _not_ work properly.
	 */
	if (bootverbose)
		if_printf(sc->hn_ifp, "disable RSS\n");
	error = hn_rndis_conf_rss(sc, NDIS_RSS_FLAG_DISABLE);
	if (error) {
		if_printf(sc->hn_ifp, "RSS disable failed\n");
		return (error);
	}

	/*
	 * Reenable the RSS w/ the updated RSS key or indirect
	 * table.
	 */
	if (bootverbose)
		if_printf(sc->hn_ifp, "reconfig RSS\n");
	error = hn_rndis_conf_rss(sc, NDIS_RSS_FLAG_NONE);
	if (error) {
		if_printf(sc->hn_ifp, "RSS reconfig failed\n");
		return (error);
	}
	return (0);
}