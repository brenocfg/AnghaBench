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
struct tpm_space {int /*<<< orphan*/ * context_tbl; } ;
struct tpm_chip {struct tpm_space work_space; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpm2_flush_context (struct tpm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm2_flush_sessions (struct tpm_chip*,struct tpm_space*) ; 

void tpm2_flush_space(struct tpm_chip *chip)
{
	struct tpm_space *space = &chip->work_space;
	int i;

	for (i = 0; i < ARRAY_SIZE(space->context_tbl); i++)
		if (space->context_tbl[i] && ~space->context_tbl[i])
			tpm2_flush_context(chip, space->context_tbl[i]);

	tpm2_flush_sessions(chip, space);
}