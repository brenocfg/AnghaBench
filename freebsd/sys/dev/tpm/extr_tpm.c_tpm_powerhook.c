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
struct tpm_softc {int dummy; } ;

/* Variables and functions */
 int PWR_RESUME ; 
 int /*<<< orphan*/  tpm_resume (struct tpm_softc*,int) ; 
 int /*<<< orphan*/  tpm_suspend (struct tpm_softc*,int) ; 

void
tpm_powerhook(int why, void *self)
{
	struct tpm_softc *sc = (struct tpm_softc *)self;

	if (why != PWR_RESUME)
		tpm_suspend(sc, why);
	else
		tpm_resume(sc, why);
}