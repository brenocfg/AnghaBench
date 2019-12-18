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
struct mpssas_softc {struct mps_softc* sc; } ;
struct mps_softc {char* exclude_ids; } ;

/* Variables and functions */
 char* strsep (char**,char*) ; 
 long strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
mpssas_check_id(struct mpssas_softc *sassc, int id)
{
	struct mps_softc *sc = sassc->sc;
	char *ids;
	char *name;

	ids = &sc->exclude_ids[0];
	while((name = strsep(&ids, ",")) != NULL) {
		if (name[0] == '\0')
			continue;
		if (strtol(name, NULL, 0) == (long)id)
			return (1);
	}

	return (0);
}