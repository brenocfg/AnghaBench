#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
struct TYPE_5__ {scalar_t__ poll_count; int poll_state; int /*<<< orphan*/  lmi_channel0; int /*<<< orphan*/  lmi_channel; int /*<<< orphan*/  lmi_channel1023; } ;

/* Variables and functions */
 scalar_t__ LMIPOLLSIZE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  SCF_ANNEX_A ; 
 int /*<<< orphan*/  SCF_ANNEX_D ; 
 int /*<<< orphan*/  SCF_GROUP4 ; 
 int /*<<< orphan*/  SETLMITYPE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nglmi_inquire (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngauto_state_machine(sc_p sc)
{
	if ((sc->poll_count <= 0) || (sc->poll_count > LMIPOLLSIZE)) {
		/* time to change states in the auto probe machine */
		/* capture wild values of poll_count while we are at it */
		sc->poll_count = LMIPOLLSIZE;
		sc->poll_state++;
	}
	switch (sc->poll_state) {
	case 7:
		log(LOG_WARNING, "nglmi: no response from exchange\n");
	default:		/* capture bad states */
		sc->poll_state = 1;
	case 1:
		sc->lmi_channel = sc->lmi_channel0;
		SETLMITYPE(sc, SCF_ANNEX_D);
		break;
	case 2:
		sc->lmi_channel = sc->lmi_channel1023;
		SETLMITYPE(sc, SCF_ANNEX_D);
		break;
	case 3:
		sc->lmi_channel = sc->lmi_channel0;
		SETLMITYPE(sc, SCF_ANNEX_A);
		break;
	case 4:
		sc->lmi_channel = sc->lmi_channel1023;
		SETLMITYPE(sc, SCF_GROUP4);
		break;
	case 5:
		sc->lmi_channel = sc->lmi_channel1023;
		SETLMITYPE(sc, SCF_ANNEX_A);
		break;
	case 6:
		sc->lmi_channel = sc->lmi_channel0;
		SETLMITYPE(sc, SCF_GROUP4);
		break;
	}

	/* send an inquirey encoded appropriately */
	nglmi_inquire(sc, 0);
	sc->poll_count--;
}