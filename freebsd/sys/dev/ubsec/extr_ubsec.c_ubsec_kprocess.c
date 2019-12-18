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
struct ubsec_softc {int sc_flags; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_q2free; } ;
struct ubsec_q2 {int dummy; } ;
struct cryptkop {int krp_op; int /*<<< orphan*/  krp_status; int /*<<< orphan*/ * krp_callback; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  CRK_MOD_EXP 129 
#define  CRK_MOD_EXP_CRT 128 
 int EINVAL ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  SIMPLEQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ubsec_q2* SIMPLEQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIMPLEQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int UBS_FLAGS_HWNORM ; 
 int /*<<< orphan*/  crypto_kdone (struct cryptkop*) ; 
 struct ubsec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  q_next ; 
 int /*<<< orphan*/  ubsec_kfree (struct ubsec_softc*,struct ubsec_q2*) ; 
 int ubsec_kprocess_modexp_hw (struct ubsec_softc*,struct cryptkop*,int) ; 
 int ubsec_kprocess_modexp_sw (struct ubsec_softc*,struct cryptkop*,int) ; 
 int ubsec_kprocess_rsapriv (struct ubsec_softc*,struct cryptkop*,int) ; 

__attribute__((used)) static int
ubsec_kprocess(device_t dev, struct cryptkop *krp, int hint)
{
	struct ubsec_softc *sc = device_get_softc(dev);
	int r;

	if (krp == NULL || krp->krp_callback == NULL)
		return (EINVAL);

	while (!SIMPLEQ_EMPTY(&sc->sc_q2free)) {
		struct ubsec_q2 *q;

		q = SIMPLEQ_FIRST(&sc->sc_q2free);
		SIMPLEQ_REMOVE_HEAD(&sc->sc_q2free, q_next);
		ubsec_kfree(sc, q);
	}

	switch (krp->krp_op) {
	case CRK_MOD_EXP:
		if (sc->sc_flags & UBS_FLAGS_HWNORM)
			r = ubsec_kprocess_modexp_hw(sc, krp, hint);
		else
			r = ubsec_kprocess_modexp_sw(sc, krp, hint);
		break;
	case CRK_MOD_EXP_CRT:
		return (ubsec_kprocess_rsapriv(sc, krp, hint));
	default:
		device_printf(sc->sc_dev, "kprocess: invalid op 0x%x\n",
		    krp->krp_op);
		krp->krp_status = EOPNOTSUPP;
		crypto_kdone(krp);
		return (0);
	}
	return (0);			/* silence compiler */
}