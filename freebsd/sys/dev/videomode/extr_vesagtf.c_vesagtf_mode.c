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
struct videomode {int dummy; } ;
struct vesagtf_params {int /*<<< orphan*/  J; int /*<<< orphan*/  K; int /*<<< orphan*/  C; int /*<<< orphan*/  M; int /*<<< orphan*/  min_vsbp; int /*<<< orphan*/  hsync_pct; int /*<<< orphan*/  vsync_rqd; int /*<<< orphan*/  min_porch; int /*<<< orphan*/  margin_ppt; } ;

/* Variables and functions */
 int /*<<< orphan*/  VESAGTF_C ; 
 int /*<<< orphan*/  VESAGTF_HSYNC_PCT ; 
 int /*<<< orphan*/  VESAGTF_J ; 
 int /*<<< orphan*/  VESAGTF_K ; 
 int /*<<< orphan*/  VESAGTF_M ; 
 int /*<<< orphan*/  VESAGTF_MARGIN_PPT ; 
 int /*<<< orphan*/  VESAGTF_MIN_PORCH ; 
 int /*<<< orphan*/  VESAGTF_MIN_VSBP ; 
 int /*<<< orphan*/  VESAGTF_VSYNC_RQD ; 
 int /*<<< orphan*/  vesagtf_mode_params (unsigned int,unsigned int,unsigned int,struct vesagtf_params*,int /*<<< orphan*/ ,struct videomode*) ; 

void
vesagtf_mode(unsigned x, unsigned y, unsigned refresh, struct videomode *vmp)
{
	struct vesagtf_params	params;

	params.margin_ppt = VESAGTF_MARGIN_PPT;
	params.min_porch = VESAGTF_MIN_PORCH;
	params.vsync_rqd = VESAGTF_VSYNC_RQD;
	params.hsync_pct = VESAGTF_HSYNC_PCT;
	params.min_vsbp = VESAGTF_MIN_VSBP;
	params.M = VESAGTF_M;
	params.C = VESAGTF_C;
	params.K = VESAGTF_K;
	params.J = VESAGTF_J;

	vesagtf_mode_params(x, y, refresh, &params, 0, vmp);
}