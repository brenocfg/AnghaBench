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
struct ccdiinfo {scalar_t__ ii_ndisk; struct ccdiinfo* sc_itable; struct ccdiinfo* ii_index; struct ccdiinfo* sc_cinfo; } ;
struct ccd_s {scalar_t__ ii_ndisk; struct ccd_s* sc_itable; struct ccd_s* ii_index; struct ccd_s* sc_cinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (struct ccdiinfo*) ; 

__attribute__((used)) static void
g_ccd_freesc(struct ccd_s *sc)
{
	struct ccdiinfo *ii;

	g_free(sc->sc_cinfo);
	if (sc->sc_itable != NULL) {
		for (ii = sc->sc_itable; ii->ii_ndisk > 0; ii++)
			if (ii->ii_index != NULL)
				g_free(ii->ii_index);
		g_free(sc->sc_itable);
	}
	g_free(sc);
}