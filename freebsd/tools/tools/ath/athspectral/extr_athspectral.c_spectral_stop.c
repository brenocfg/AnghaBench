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
struct TYPE_2__ {int ad_id; int ad_out_size; int /*<<< orphan*/  ad_name; scalar_t__ ad_out_data; scalar_t__ ad_in_size; int /*<<< orphan*/ * ad_in_data; } ;
struct spectralhandler {TYPE_1__ atd; int /*<<< orphan*/  s; } ;
typedef  int /*<<< orphan*/  pe ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  HAL_SPECTRAL_PARAM ;

/* Variables and functions */
 int ATH_DIAG_DYN ; 
 int /*<<< orphan*/  SIOCGATHSPECTRAL ; 
 int SPECTRAL_CONTROL_STOP ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
spectral_stop(struct spectralhandler *spectral)
{
	HAL_SPECTRAL_PARAM pe;

	spectral->atd.ad_id = SPECTRAL_CONTROL_STOP | ATH_DIAG_DYN;
	memset(&pe, 0, sizeof(pe));

	/*
	 * XXX don't need these, but need to eliminate the ATH_DIAG_DYN flag
	 * and debug
	 */
	spectral->atd.ad_in_data = NULL;
	spectral->atd.ad_in_size = 0;
	spectral->atd.ad_out_data = (caddr_t) &pe;
	spectral->atd.ad_out_size = sizeof(pe);

	if (ioctl(spectral->s, SIOCGATHSPECTRAL, &spectral->atd) < 0)
		err(1, "%s", spectral->atd.ad_name);
}