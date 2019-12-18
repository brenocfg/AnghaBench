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
typedef  size_t u_int ;
struct apm_softc {int sc_flags; size_t event_count; scalar_t__* event_filter; size_t event_ptr; int /*<<< orphan*/  sc_rsel; struct apm_event_info* event_list; } ;
struct apm_event_info {size_t type; scalar_t__ index; } ;

/* Variables and functions */
 size_t APM_NEVENTS ; 
 int /*<<< orphan*/  PZERO ; 
 int SCFLAG_OCTL ; 
 int SCFLAG_OPEN ; 
 scalar_t__ apm_evindex ; 
 int /*<<< orphan*/  selwakeuppri (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
apm_record_event(struct apm_softc *sc, u_int event_type)
{
	struct apm_event_info *evp;

	if ((sc->sc_flags & SCFLAG_OPEN) == 0)
		return 1;		/* no user waiting */
	if (sc->event_count == APM_NEVENTS)
		return 1;			/* overflow */
	if (sc->event_filter[event_type] == 0)
		return 1;		/* not registered */
	evp = &sc->event_list[sc->event_ptr];
	sc->event_count++;
	sc->event_ptr++;
	sc->event_ptr %= APM_NEVENTS;
	evp->type = event_type;
	evp->index = ++apm_evindex;
	selwakeuppri(&sc->sc_rsel, PZERO);
	return (sc->sc_flags & SCFLAG_OCTL) ? 0 : 1; /* user may handle */
}