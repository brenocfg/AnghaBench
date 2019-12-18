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
typedef  scalar_t__ u_int32_t ;
struct ath_softc {int dummy; } ;
struct ath_diag {unsigned int ad_id; scalar_t__ ad_in_size; scalar_t__ ad_out_size; int /*<<< orphan*/  ad_out_data; int /*<<< orphan*/  ad_in_data; } ;

/* Variables and functions */
 int ATH_DIAG_DYN ; 
 unsigned int ATH_DIAG_ID ; 
 int ATH_DIAG_IN ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_ZERO ; 
 int copyin (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 scalar_t__ copyout (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 void* malloc (scalar_t__,int /*<<< orphan*/ ,int) ; 

int
ath_lna_div_ioctl(struct ath_softc *sc, struct ath_diag *ad)
{
	unsigned int id = ad->ad_id & ATH_DIAG_ID;
	void *indata = NULL;
	void *outdata = NULL;
	u_int32_t insize = ad->ad_in_size;
	u_int32_t outsize = ad->ad_out_size;
	int error = 0;
//	int val;

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
	return (error);
}