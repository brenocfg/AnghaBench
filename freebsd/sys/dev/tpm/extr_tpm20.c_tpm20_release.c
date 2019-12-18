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
struct tpm_sc {int /*<<< orphan*/ * sc_cdev; int /*<<< orphan*/  buf_cv; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/ * buf; int /*<<< orphan*/  harvest_callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TPM20 ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

void
tpm20_release(struct tpm_sc *sc)
{

#ifdef TPM_HARVEST
	callout_drain(&sc->harvest_callout);
#endif

	if (sc->buf != NULL)
		free(sc->buf, M_TPM20);

	sx_destroy(&sc->dev_lock);
	cv_destroy(&sc->buf_cv);
	if (sc->sc_cdev != NULL)
		destroy_dev(sc->sc_cdev);
}