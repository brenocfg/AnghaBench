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
typedef  int /*<<< orphan*/  uint8_t ;
struct powernow_state {scalar_t__ freq; size_t fid; int vid; void* power; } ;
struct pn_softc {int pn_type; int fsb; int errata; int powernow_max_states; struct powernow_state* powernow_states; } ;

/* Variables and functions */
 int A0_ERRATA ; 
 void* CPUFREQ_VAL_UNKNOWN ; 
#define  PN7_TYPE 129 
#define  PN8_TYPE 128 
 int POWERNOW_MAX_STATES ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  memcpy (struct powernow_state*,struct powernow_state*,int) ; 
 int* pn7_fid_to_mult ; 
 int* pn8_fid_to_mult ; 
 int /*<<< orphan*/  printf (char*,int,scalar_t__,int,int) ; 

__attribute__((used)) static int
decode_pst(struct pn_softc *sc, uint8_t *p, int npstates)
{
	int i, j, n;
	struct powernow_state state;

	for (i = 0; i < POWERNOW_MAX_STATES; ++i)
		sc->powernow_states[i].freq = CPUFREQ_VAL_UNKNOWN;

	for (n = 0, i = 0; i < npstates; ++i) {
		state.fid = *p++;
		state.vid = *p++;
		state.power = CPUFREQ_VAL_UNKNOWN;

		switch (sc->pn_type) {
		case PN7_TYPE:
			state.freq = 100 * pn7_fid_to_mult[state.fid] * sc->fsb;
			if ((sc->errata & A0_ERRATA) &&
			    (pn7_fid_to_mult[state.fid] % 10) == 5)
				continue;
			break;
		case PN8_TYPE:
			state.freq = 100 * pn8_fid_to_mult[state.fid] * sc->fsb;
			break;
		}

		j = n;
		while (j > 0 && sc->powernow_states[j - 1].freq < state.freq) {
			memcpy(&sc->powernow_states[j],
			    &sc->powernow_states[j - 1],
			    sizeof(struct powernow_state));
			--j;
		}
		memcpy(&sc->powernow_states[j], &state,
		    sizeof(struct powernow_state));
		++n;
	}

	/*
	 * Fix powernow_max_states, if errata a0 give us less states
	 * than expected.
	 */
	sc->powernow_max_states = n;

	if (bootverbose)
		for (i = 0; i < sc->powernow_max_states; ++i) {
			int fid = sc->powernow_states[i].fid;
			int vid = sc->powernow_states[i].vid;

			printf("powernow: %2i %8dkHz FID %02x VID %02x\n",
			    i,
			    sc->powernow_states[i].freq,
			    fid,
			    vid);
		}

	return (0);
}