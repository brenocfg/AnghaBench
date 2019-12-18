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
struct tpm_space {int /*<<< orphan*/  session_buf; int /*<<< orphan*/  context_buf; } ;
struct tpm_chip {int /*<<< orphan*/  tpm_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpm2_flush_sessions (struct tpm_chip*,struct tpm_space*) ; 
 int /*<<< orphan*/  tpm_chip_start (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_chip_stop (struct tpm_chip*) ; 

void tpm2_del_space(struct tpm_chip *chip, struct tpm_space *space)
{
	mutex_lock(&chip->tpm_mutex);
	if (!tpm_chip_start(chip)) {
		tpm2_flush_sessions(chip, space);
		tpm_chip_stop(chip);
	}
	mutex_unlock(&chip->tpm_mutex);
	kfree(space->context_buf);
	kfree(space->session_buf);
}