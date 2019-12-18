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
struct z_info {int z_size; int z_gy; int z_gx; int z_dx; int z_coeff; int z_dy; void** z_pcoeff; } ;
typedef  int intmax_t ;
typedef  int int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int E2BIG ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int Z_MASK ; 
 int Z_SHIFT ; 
 int feeder_rate_polyphase_max ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int /*<<< orphan*/  free (void**,int /*<<< orphan*/ ) ; 
 void** malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 void* z_coeff_interpolate (int,int) ; 

__attribute__((used)) static int
z_resampler_build_polyphase(struct z_info *info)
{
	int32_t alpha, c, i, z, idx;

	/* Let this be here first. */
	if (info->z_pcoeff != NULL) {
		free(info->z_pcoeff, M_DEVBUF);
		info->z_pcoeff = NULL;
	}

	if (feeder_rate_polyphase_max < 1)
		return (ENOTSUP);

	if (((int64_t)info->z_size * info->z_gy * 2) >
	    feeder_rate_polyphase_max) {
#ifndef _KERNEL
		fprintf(stderr, "Polyphase entries exceed: [%d/%d] %jd > %d\n",
		    info->z_gx, info->z_gy,
		    (intmax_t)info->z_size * info->z_gy * 2,
		    feeder_rate_polyphase_max);
#endif
		return (E2BIG);
	}

	info->z_pcoeff = malloc(sizeof(int32_t) *
	    info->z_size * info->z_gy * 2, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (info->z_pcoeff == NULL)
		return (ENOMEM);

	for (alpha = 0; alpha < info->z_gy; alpha++) {
		z = alpha * info->z_dx;
		c = 0;
		for (i = info->z_size; i != 0; i--) {
			c += z >> Z_SHIFT;
			z &= Z_MASK;
			idx = (alpha * info->z_size * 2) +
			    (info->z_size * 2) - i;
			info->z_pcoeff[idx] =
			    z_coeff_interpolate(z, info->z_coeff + c);
			z += info->z_dy;
		}
		z = info->z_dy - (alpha * info->z_dx);
		c = 0;
		for (i = info->z_size; i != 0; i--) {
			c += z >> Z_SHIFT;
			z &= Z_MASK;
			idx = (alpha * info->z_size * 2) + i - 1;
			info->z_pcoeff[idx] =
			    z_coeff_interpolate(z, info->z_coeff + c);
			z += info->z_dy;
		}
	}
	
#ifndef _KERNEL
	fprintf(stderr, "Polyphase: [%d/%d] %d entries\n",
	    info->z_gx, info->z_gy, info->z_size * info->z_gy * 2);
#endif

	return (0);
}