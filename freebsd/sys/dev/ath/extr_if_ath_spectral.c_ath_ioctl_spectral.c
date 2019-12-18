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
typedef  int u_int32_t ;
struct ath_spectral_state {int spectral_enable_after_reset; int /*<<< orphan*/  spectral_state; } ;
struct ath_softc {int sc_dospectral; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_ah; struct ath_spectral_state* sc_spectral; } ;
struct ath_diag {unsigned int ad_id; int ad_in_size; int ad_out_size; int /*<<< orphan*/  ad_out_data; int /*<<< orphan*/  ad_in_data; } ;
typedef  int /*<<< orphan*/  peout ;
typedef  int /*<<< orphan*/  HAL_SPECTRAL_PARAM ;

/* Variables and functions */
 int ATH_DIAG_DYN ; 
 unsigned int ATH_DIAG_ID ; 
 int ATH_DIAG_IN ; 
 int /*<<< orphan*/  ATH_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_UNLOCK (struct ath_softc*) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_ZERO ; 
#define  SPECTRAL_CONTROL_DISABLE 134 
#define  SPECTRAL_CONTROL_ENABLE 133 
#define  SPECTRAL_CONTROL_ENABLE_AT_RESET 132 
#define  SPECTRAL_CONTROL_GET_PARAMS 131 
#define  SPECTRAL_CONTROL_SET_PARAMS 130 
#define  SPECTRAL_CONTROL_START 129 
#define  SPECTRAL_CONTROL_STOP 128 
 int /*<<< orphan*/  ath_hal_spectral_configure (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_hal_spectral_get_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_hal_spectral_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_spectral_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_spectral_supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_power_restore_power_state (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_power_set_power_state (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int copyin (int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ copyout (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
ath_ioctl_spectral(struct ath_softc *sc, struct ath_diag *ad)
{
	unsigned int id = ad->ad_id & ATH_DIAG_ID;
	void *indata = NULL;
	void *outdata = NULL;
	u_int32_t insize = ad->ad_in_size;
	u_int32_t outsize = ad->ad_out_size;
	int error = 0;
	HAL_SPECTRAL_PARAM peout;
	HAL_SPECTRAL_PARAM *pe;
	struct ath_spectral_state *ss = sc->sc_spectral;
	int val;

	if (! ath_hal_spectral_supported(sc->sc_ah))
		return (EINVAL);

	ATH_LOCK(sc);
	ath_power_set_power_state(sc, HAL_PM_AWAKE);
	ATH_UNLOCK(sc);

	if (ad->ad_id & ATH_DIAG_IN) {
		/*
		 * Copy in data.
		 */
		indata = malloc(insize, M_TEMP, M_NOWAIT);
		if (indata == NULL) {
			error = ENOMEM;
			goto bad;
		}
		error = copyin(ad->ad_in_data, indata, insize);
		if (error)
			goto bad;
	}
	if (ad->ad_id & ATH_DIAG_DYN) {
		/*
		 * Allocate a buffer for the results (otherwise the HAL
		 * returns a pointer to a buffer where we can read the
		 * results).  Note that we depend on the HAL leaving this
		 * pointer for us to use below in reclaiming the buffer;
		 * may want to be more defensive.
		 */
		outdata = malloc(outsize, M_TEMP, M_NOWAIT | M_ZERO);
		if (outdata == NULL) {
			error = ENOMEM;
			goto bad;
		}
	}
	switch (id) {
		case SPECTRAL_CONTROL_GET_PARAMS:
			memset(&peout, 0, sizeof(peout));
			outsize = sizeof(HAL_SPECTRAL_PARAM);
			ath_hal_spectral_get_config(sc->sc_ah, &peout);
			pe = (HAL_SPECTRAL_PARAM *) outdata;
			memcpy(pe, &peout, sizeof(*pe));
			break;
		case SPECTRAL_CONTROL_SET_PARAMS:
			if (insize < sizeof(HAL_SPECTRAL_PARAM)) {
				error = EINVAL;
				break;
			}
			pe = (HAL_SPECTRAL_PARAM *) indata;
			ath_hal_spectral_configure(sc->sc_ah, pe);
			/* Save a local copy of the updated parameters */
			ath_hal_spectral_get_config(sc->sc_ah,
			    &ss->spectral_state);
			break;
		case SPECTRAL_CONTROL_START:
			ath_hal_spectral_configure(sc->sc_ah,
			    &ss->spectral_state);
			(void) ath_hal_spectral_start(sc->sc_ah);
			sc->sc_dospectral = 1;
			/* XXX need to update the PHY mask in the driver */
			break;
		case SPECTRAL_CONTROL_STOP:
			(void) ath_hal_spectral_stop(sc->sc_ah);
			sc->sc_dospectral = 0;
			/* XXX need to update the PHY mask in the driver */
			break;
		case SPECTRAL_CONTROL_ENABLE_AT_RESET:
			if (insize < sizeof(int)) {
				device_printf(sc->sc_dev, "%d != %d\n",
				    insize,
				    (int) sizeof(int));
				error = EINVAL;
				break;
			}
			if (indata == NULL) {
				device_printf(sc->sc_dev, "indata=NULL\n");
				error = EINVAL;
				break;
			}
			val = * ((int *) indata);
			if (val == 0)
				ss->spectral_enable_after_reset = 0;
			else
				ss->spectral_enable_after_reset = 1;
			break;
		case SPECTRAL_CONTROL_ENABLE:
			/* XXX TODO */
		case SPECTRAL_CONTROL_DISABLE:
			/* XXX TODO */
		break;
		default:
			error = EINVAL;
			goto bad;
	}
	if (outsize < ad->ad_out_size)
		ad->ad_out_size = outsize;
	if (outdata && copyout(outdata, ad->ad_out_data, ad->ad_out_size))
		error = EFAULT;
bad:
	if ((ad->ad_id & ATH_DIAG_IN) && indata != NULL)
		free(indata, M_TEMP);
	if ((ad->ad_id & ATH_DIAG_DYN) && outdata != NULL)
		free(outdata, M_TEMP);
	ATH_LOCK(sc);
	ath_power_restore_power_state(sc);
	ATH_UNLOCK(sc);

	return (error);
}