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
struct tpm_space {scalar_t__* session_tbl; } ;
struct tpm_chip {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  tpm2_flush_context (struct tpm_chip*,scalar_t__) ; 

__attribute__((used)) static void tpm2_flush_sessions(struct tpm_chip *chip, struct tpm_space *space)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(space->session_tbl); i++) {
		if (space->session_tbl[i])
			tpm2_flush_context(chip, space->session_tbl[i]);
	}
}