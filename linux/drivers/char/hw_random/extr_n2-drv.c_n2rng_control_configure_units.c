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
typedef  int u64 ;
struct n2rng_unit {int* control; } ;
struct n2rng {int num_units; int accum_cycles; TYPE_1__* data; struct n2rng_unit* units; } ;
struct TYPE_2__ {int chip_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_RNG_STATE_CONFIGURED ; 
 int RNG_CTL_ES1 ; 
 int RNG_CTL_ES2 ; 
 int RNG_CTL_ES3 ; 
 int RNG_CTL_LFSR ; 
 int RNG_v1_CTL_ASEL_NOOUT ; 
 int RNG_v1_CTL_ASEL_SHIFT ; 
 int RNG_v1_CTL_VCO_SHIFT ; 
 int RNG_v1_CTL_WAIT_SHIFT ; 
 int RNG_v2_CTL_ASEL_NOOUT ; 
 int RNG_v2_CTL_ASEL_SHIFT ; 
 int RNG_v2_CTL_VCO_SHIFT ; 
 int RNG_v2_CTL_WAIT_SHIFT ; 
 unsigned long __pa (int*) ; 
 int n2rng_generic_write_control (struct n2rng*,unsigned long,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int n2rng_control_configure_units(struct n2rng *np)
{
	int unit, err;

	err = 0;
	for (unit = 0; unit < np->num_units; unit++) {
		struct n2rng_unit *up = &np->units[unit];
		unsigned long ctl_ra = __pa(&up->control[0]);
		int esrc;
		u64 base, shift;

		if (np->data->chip_version == 1) {
			base = ((np->accum_cycles << RNG_v1_CTL_WAIT_SHIFT) |
			      (RNG_v1_CTL_ASEL_NOOUT << RNG_v1_CTL_ASEL_SHIFT) |
			      RNG_CTL_LFSR);
			shift = RNG_v1_CTL_VCO_SHIFT;
		} else {
			base = ((np->accum_cycles << RNG_v2_CTL_WAIT_SHIFT) |
			      (RNG_v2_CTL_ASEL_NOOUT << RNG_v2_CTL_ASEL_SHIFT) |
			      RNG_CTL_LFSR);
			shift = RNG_v2_CTL_VCO_SHIFT;
		}

		/* XXX This isn't the best.  We should fetch a bunch
		 * XXX of words using each entropy source combined XXX
		 * with each VCO setting, and see which combinations
		 * XXX give the best random data.
		 */
		for (esrc = 0; esrc < 3; esrc++)
			up->control[esrc] = base |
				(esrc << shift) |
				(RNG_CTL_ES1 << esrc);

		up->control[3] = base |
			(RNG_CTL_ES1 | RNG_CTL_ES2 | RNG_CTL_ES3);

		err = n2rng_generic_write_control(np, ctl_ra, unit,
						  HV_RNG_STATE_CONFIGURED);
		if (err)
			break;
	}

	return err;
}