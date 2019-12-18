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
struct bxe_softc {scalar_t__ panic; } ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_EMUL (struct bxe_softc*) ; 
 int /*<<< orphan*/  ECORE_ERR (char*,int) ; 
 int ECORE_IO ; 
 int /*<<< orphan*/  ECORE_MIGHT_SLEEP () ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,int) ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ECORE_TEST_BIT (int,unsigned long*) ; 
 int ECORE_TIMEOUT ; 
 int /*<<< orphan*/  ECORE_WAIT (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delay_us ; 
 int /*<<< orphan*/  ecore_panic () ; 

__attribute__((used)) static inline int ecore_state_wait(struct bxe_softc *sc, int state,
				   unsigned long *pstate)
{
	/* can take a while if any port is running */
	int cnt = 5000;


	if (CHIP_REV_IS_EMUL(sc))
		cnt *= 20;

	ECORE_MSG(sc, "waiting for state to become %d\n", state);

	ECORE_MIGHT_SLEEP();
	while (cnt--) {
		if (!ECORE_TEST_BIT(state, pstate)) {
#ifdef ECORE_STOP_ON_ERROR
			ECORE_MSG(sc, "exit  (cnt %d)\n", 5000 - cnt);
#endif
			return ECORE_SUCCESS;
		}

		ECORE_WAIT(sc, delay_us);

		if (sc->panic)
			return ECORE_IO;
	}

	/* timeout! */
	ECORE_ERR("timeout waiting for state %d\n", state);
#ifdef ECORE_STOP_ON_ERROR
	ecore_panic();
#endif

	return ECORE_TIMEOUT;
}