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
struct z_info {int src; int rsrc; int dst; int rdst; int z_gx; int z_gy; int z_size; scalar_t__ quality; scalar_t__ z_cycle; void* z_dy; void* z_dx; int /*<<< orphan*/  z_scale; int /*<<< orphan*/ * z_pcoeff; int /*<<< orphan*/ * z_dcoeff; int /*<<< orphan*/ * z_coeff; int /*<<< orphan*/ * z_resample; scalar_t__ z_alpha; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 void* Z_FULL_ONE ; 
 int /*<<< orphan*/  Z_ONE ; 
 scalar_t__ Z_QUALITY_MAX ; 
 scalar_t__ Z_QUALITY_MIN ; 
 int feeder_rate_round ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
z_resampler_reset(struct z_info *info)
{

	info->src = info->rsrc - (info->rsrc % ((feeder_rate_round > 0 &&
	    info->rsrc > feeder_rate_round) ? feeder_rate_round : 1));
	info->dst = info->rdst - (info->rdst % ((feeder_rate_round > 0 &&
	    info->rdst > feeder_rate_round) ? feeder_rate_round : 1));
	info->z_gx = 1;
	info->z_gy = 1;
	info->z_alpha = 0;
	info->z_resample = NULL;
	info->z_size = 1;
	info->z_coeff = NULL;
	info->z_dcoeff = NULL;
	if (info->z_pcoeff != NULL) {
		free(info->z_pcoeff, M_DEVBUF);
		info->z_pcoeff = NULL;
	}
	info->z_scale = Z_ONE;
	info->z_dx = Z_FULL_ONE;
	info->z_dy = Z_FULL_ONE;
#ifdef Z_DIAGNOSTIC
	info->z_cycle = 0;
#endif
	if (info->quality < Z_QUALITY_MIN)
		info->quality = Z_QUALITY_MIN;
	else if (info->quality > Z_QUALITY_MAX)
		info->quality = Z_QUALITY_MAX;
}