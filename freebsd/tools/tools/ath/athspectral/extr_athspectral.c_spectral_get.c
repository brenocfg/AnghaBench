#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ad_id; int ad_out_size; int /*<<< orphan*/  ad_name; scalar_t__ ad_out_data; scalar_t__ ad_in_size; int /*<<< orphan*/ * ad_in_data; } ;
struct spectralhandler {TYPE_3__ atd; int /*<<< orphan*/  s; } ;
typedef  int /*<<< orphan*/  pe ;
typedef  scalar_t__ caddr_t ;
struct TYPE_4__ {int ss_enabled; int ss_active; int ss_count; int ss_fft_period; int ss_period; int ss_short_report; int ss_spectral_pri; int radar_bin_thresh_sel; } ;
typedef  TYPE_1__ HAL_SPECTRAL_PARAM ;

/* Variables and functions */
 int ATH_DIAG_DYN ; 
 int /*<<< orphan*/  SIOCGATHSPECTRAL ; 
 int SPECTRAL_CONTROL_GET_PARAMS ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
spectral_get(struct spectralhandler *spectral)
{
	HAL_SPECTRAL_PARAM pe;

	spectral->atd.ad_id = SPECTRAL_CONTROL_GET_PARAMS | ATH_DIAG_DYN;
	memset(&pe, 0, sizeof(pe));

	spectral->atd.ad_in_data = NULL;
	spectral->atd.ad_in_size = 0;
	spectral->atd.ad_out_data = (caddr_t) &pe;
	spectral->atd.ad_out_size = sizeof(pe);

	if (ioctl(spectral->s, SIOCGATHSPECTRAL, &spectral->atd) < 0)
		err(1, "%s", spectral->atd.ad_name);

	printf("Spectral parameters (raw):\n");
	printf("   ss_enabled: %d\n", pe.ss_enabled);
	printf("   ss_active: %d\n", pe.ss_active);
	printf("   ss_count: %d\n", pe.ss_count);
	printf("   ss_fft_period: %d\n", pe.ss_fft_period);
	printf("   ss_period: %d\n", pe.ss_period);
	printf("   ss_short_report: %d\n", pe.ss_short_report);
	printf("   ss_spectral_pri: %d\n", pe.ss_spectral_pri);
	printf("   radar_bin_thresh_sel: %d\n", pe.radar_bin_thresh_sel);
}