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
struct mpc85xx_jog_softc {scalar_t__ min_freq; } ;
struct jog_rv_args {int slow; int inprogress; int /*<<< orphan*/  cpu; int /*<<< orphan*/  mult; } ;
struct cf_setting {scalar_t__ freq; int /*<<< orphan*/ * spec; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 struct mpc85xx_jog_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc85xx_jog_set_int ; 
 int /*<<< orphan*/  smp_no_rendezvous_barrier ; 
 int /*<<< orphan*/  smp_rendezvous (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jog_rv_args*) ; 

__attribute__((used)) static int
mpc85xx_jog_set(device_t dev, const struct cf_setting *set)
{
	struct mpc85xx_jog_softc *sc;
	struct jog_rv_args args;
	
	if (set == NULL)
		return (EINVAL);

	sc = device_get_softc(dev);

	args.slow = (set->freq <= sc->min_freq);
	args.mult = set->spec[0];
	args.cpu = PCPU_GET(cpuid);
	args.inprogress = 1;
	smp_rendezvous(smp_no_rendezvous_barrier, mpc85xx_jog_set_int,
	    smp_no_rendezvous_barrier, &args);

	return (0);
}