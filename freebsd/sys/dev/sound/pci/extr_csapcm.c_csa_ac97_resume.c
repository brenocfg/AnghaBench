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
struct csa_info {int /*<<< orphan*/ * ac97; int /*<<< orphan*/  res; int /*<<< orphan*/  ac97_powerdown; int /*<<< orphan*/  ac97_general_purpose; } ;

/* Variables and functions */
 scalar_t__ BA0_AC97_GENERAL_PURPOSE ; 
 scalar_t__ BA0_AC97_POWERDOWN ; 
 scalar_t__ BA0_AC97_RESET ; 
 int CS461x_AC97_HIGHESTREGTORESTORE ; 
 int CS461x_AC97_NUMBER_RESTORE_REGS ; 
 int /*<<< orphan*/  csa_writecodec (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csa_ac97_resume(struct csa_info *csa)
{
	int count, i;

	/*
	 * First, we restore the state of the general purpose register.  This
	 * contains the mic select (mic1 or mic2) and if we restore this after
	 * we restore the mic volume/boost state and mic2 was selected at
	 * suspend time, we will end up with a brief period of time where mic1
	 * is selected with the volume/boost settings for mic2, causing
	 * acoustic feedback.  So we restore the general purpose register
	 * first, thereby getting the correct mic selected before we restore
	 * the mic volume/boost.
	 */
	csa_writecodec(&csa->res, BA0_AC97_GENERAL_PURPOSE,
	    csa->ac97_general_purpose);
	/*
	 * Now, while the outputs are still muted, restore the state of power
	 * on the AC97 part.
	 */
	csa_writecodec(&csa->res, BA0_AC97_POWERDOWN, csa->ac97_powerdown);
	/*
	 * Restore just the first set of registers, from register number
	 * 0x02 to the register number that ulHighestRegToRestore specifies.
	 */
	for (count = 0x2, i=0;
	    (count <= CS461x_AC97_HIGHESTREGTORESTORE) &&
	    (i < CS461x_AC97_NUMBER_RESTORE_REGS);
	    count += 2, i++)
		csa_writecodec(&csa->res, BA0_AC97_RESET + count, csa->ac97[i]);
}