#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ath_driver_req {int dummy; } ;
struct ath_diag {int ad_out_size; int /*<<< orphan*/  ad_name; scalar_t__ ad_out_data; int /*<<< orphan*/  ad_id; } ;
typedef  int /*<<< orphan*/  state ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int noiseImmunityLevel; int cckNoiseImmunityLevel; int spurImmunityLevel; int firstepLevel; int ofdmWeakSigDetectOff; int cckWeakSigThreshold; int mrcCck; } ;
typedef  TYPE_1__ HAL_ANI_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_DIAG_ANI_CURRENT ; 
 int /*<<< orphan*/  SIOCGATHDIAG ; 
 scalar_t__ ath_driver_req_fetch_diag (struct ath_driver_req*,int /*<<< orphan*/ ,struct ath_diag*) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
ani_read_state(struct ath_driver_req *req, const char *ifname)
{
	struct ath_diag atd;
	HAL_ANI_STATE state;

	/*
	 * Whilst we're doing the ath_diag pieces, we have to set this
	 * ourselves.
	 */
	strncpy(atd.ad_name, ifname, sizeof (atd.ad_name));

	atd.ad_id = HAL_DIAG_ANI_CURRENT; /* XXX | DIAG_DYN? */
	atd.ad_out_data = (caddr_t) &state;
	atd.ad_out_size = sizeof(state);

	if (ath_driver_req_fetch_diag(req, SIOCGATHDIAG, &atd) < 0)
		err(1, "%s", atd.ad_name);


	printf("  ofdm_noise_immunity_level=%d\n", state.noiseImmunityLevel);
	printf("  cck_noise_immunity_level=%d\n", state.cckNoiseImmunityLevel);
	printf("  spur_immunity_level=%d\n", state.spurImmunityLevel);
	printf("  firstep_level=%d\n", state.firstepLevel);
	printf("  ofdm_weak_signal_detect=%d\n", state.ofdmWeakSigDetectOff);
	printf("  cck_weak_signal_threshold=%d\n", state.cckWeakSigThreshold);
	printf("  mrc_cck=%d\n", state.mrcCck);
	/* XXX TODO: cycle counts? */
}