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
typedef  scalar_t__ u32 ;
struct tpm_space {int* context_tbl; int* session_tbl; int /*<<< orphan*/  session_buf; int /*<<< orphan*/  context_buf; } ;
struct tpm_chip {int /*<<< orphan*/  dev; struct tpm_space work_space; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EFAULT ; 
 int ENOENT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tpm2_flush_space (struct tpm_chip*) ; 
 int tpm2_load_context (struct tpm_chip*,int /*<<< orphan*/ ,unsigned int*,scalar_t__*) ; 

__attribute__((used)) static int tpm2_load_space(struct tpm_chip *chip)
{
	struct tpm_space *space = &chip->work_space;
	unsigned int offset;
	int i;
	int rc;

	for (i = 0, offset = 0; i < ARRAY_SIZE(space->context_tbl); i++) {
		if (!space->context_tbl[i])
			continue;

		/* sanity check, should never happen */
		if (~space->context_tbl[i]) {
			dev_err(&chip->dev, "context table is inconsistent");
			return -EFAULT;
		}

		rc = tpm2_load_context(chip, space->context_buf, &offset,
				       &space->context_tbl[i]);
		if (rc)
			return rc;
	}

	for (i = 0, offset = 0; i < ARRAY_SIZE(space->session_tbl); i++) {
		u32 handle;

		if (!space->session_tbl[i])
			continue;

		rc = tpm2_load_context(chip, space->session_buf,
				       &offset, &handle);
		if (rc == -ENOENT) {
			/* load failed, just forget session */
			space->session_tbl[i] = 0;
		} else if (rc) {
			tpm2_flush_space(chip);
			return rc;
		}
		if (handle != space->session_tbl[i]) {
			dev_warn(&chip->dev, "session restored to wrong handle\n");
			tpm2_flush_space(chip);
			return -EFAULT;
		}
	}

	return 0;
}