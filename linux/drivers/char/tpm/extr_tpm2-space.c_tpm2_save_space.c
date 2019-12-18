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
struct tpm_space {int /*<<< orphan*/ * session_tbl; int /*<<< orphan*/  session_buf; int /*<<< orphan*/ * context_tbl; int /*<<< orphan*/  context_buf; } ;
struct tpm_chip {struct tpm_space work_space; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOENT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  tpm2_flush_context (struct tpm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm2_flush_space (struct tpm_chip*) ; 
 int tpm2_save_context (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int tpm2_save_space(struct tpm_chip *chip)
{
	struct tpm_space *space = &chip->work_space;
	unsigned int offset;
	int i;
	int rc;

	for (i = 0, offset = 0; i < ARRAY_SIZE(space->context_tbl); i++) {
		if (!(space->context_tbl[i] && ~space->context_tbl[i]))
			continue;

		rc = tpm2_save_context(chip, space->context_tbl[i],
				       space->context_buf, PAGE_SIZE,
				       &offset);
		if (rc == -ENOENT) {
			space->context_tbl[i] = 0;
			continue;
		} else if (rc)
			return rc;

		tpm2_flush_context(chip, space->context_tbl[i]);
		space->context_tbl[i] = ~0;
	}

	for (i = 0, offset = 0; i < ARRAY_SIZE(space->session_tbl); i++) {
		if (!space->session_tbl[i])
			continue;

		rc = tpm2_save_context(chip, space->session_tbl[i],
				       space->session_buf, PAGE_SIZE,
				       &offset);

		if (rc == -ENOENT) {
			/* handle error saving session, just forget it */
			space->session_tbl[i] = 0;
		} else if (rc < 0) {
			tpm2_flush_space(chip);
			return rc;
		}
	}

	return 0;
}