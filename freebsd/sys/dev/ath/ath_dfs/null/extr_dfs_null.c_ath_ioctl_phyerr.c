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
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct ath_diag {unsigned int ad_id; int ad_in_size; int ad_out_size; int /*<<< orphan*/  ad_out_data; int /*<<< orphan*/  ad_in_data; } ;
typedef  int /*<<< orphan*/  peout ;
typedef  int /*<<< orphan*/  HAL_PHYERR_PARAM ;

/* Variables and functions */
 int ATH_DIAG_DYN ; 
 unsigned int ATH_DIAG_ID ; 
 int ATH_DIAG_IN ; 
#define  DFS_GET_THRESH 129 
#define  DFS_SET_THRESH 128 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  ath_hal_enabledfs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_hal_getdfsthresh (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int copyin (int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ copyout (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
ath_ioctl_phyerr(struct ath_softc *sc, struct ath_diag *ad)
{
	unsigned int id = ad->ad_id & ATH_DIAG_ID;
	void *indata = NULL;
	void *outdata = NULL;
	u_int32_t insize = ad->ad_in_size;
	u_int32_t outsize = ad->ad_out_size;
	int error = 0;
	HAL_PHYERR_PARAM peout;
	HAL_PHYERR_PARAM *pe;

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
		outdata = malloc(outsize, M_TEMP, M_NOWAIT);
		if (outdata == NULL) {
			error = ENOMEM;
			goto bad;
		}
	}
	switch (id) {
		case DFS_SET_THRESH:
			if (insize < sizeof(HAL_PHYERR_PARAM)) {
				error = EINVAL;
				break;
			}
			pe = (HAL_PHYERR_PARAM *) indata;
			ath_hal_enabledfs(sc->sc_ah, pe);
			break;
		case DFS_GET_THRESH:
			memset(&peout, 0, sizeof(peout));
			outsize = sizeof(HAL_PHYERR_PARAM);
			ath_hal_getdfsthresh(sc->sc_ah, &peout);
			pe = (HAL_PHYERR_PARAM *) outdata;
			memcpy(pe, &peout, sizeof(*pe));
			break;
		default:
			error = EINVAL;
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
	return (error);
}