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
struct ip_moptions {int /*<<< orphan*/ * imo_multicast_ifp; int /*<<< orphan*/  imo_head; } ;
struct pfsync_softc {struct ip_moptions sc_imo; } ;
struct in_mfilter {int /*<<< orphan*/  imf_inm; } ;

/* Variables and functions */
 int /*<<< orphan*/  in_leavegroup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct in_mfilter* ip_mfilter_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_mfilter_free (struct in_mfilter*) ; 
 int /*<<< orphan*/  ip_mfilter_remove (int /*<<< orphan*/ *,struct in_mfilter*) ; 

__attribute__((used)) static void
pfsync_multicast_cleanup(struct pfsync_softc *sc)
{
	struct ip_moptions *imo = &sc->sc_imo;
	struct in_mfilter *imf;

	while ((imf = ip_mfilter_first(&imo->imo_head)) != NULL) {
		ip_mfilter_remove(&imo->imo_head, imf);
		in_leavegroup(imf->imf_inm, NULL);
		ip_mfilter_free(imf);
	}
	imo->imo_multicast_ifp = NULL;
}