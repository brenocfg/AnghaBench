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
struct si_sm_data {scalar_t__ error_retries; int /*<<< orphan*/  smic_timeout; int /*<<< orphan*/  state; scalar_t__ read_pos; scalar_t__ write_pos; int /*<<< orphan*/  orig_write_count; int /*<<< orphan*/  write_count; } ;

/* Variables and functions */
 int SMIC_DEBUG_ENABLE ; 
 int /*<<< orphan*/  SMIC_HOSED ; 
 scalar_t__ SMIC_MAX_ERROR_RETRIES ; 
 int /*<<< orphan*/  SMIC_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  SMIC_START_OP ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 
 int smic_debug ; 

__attribute__((used)) static inline void start_error_recovery(struct si_sm_data *smic, char *reason)
{
	(smic->error_retries)++;
	if (smic->error_retries > SMIC_MAX_ERROR_RETRIES) {
		if (smic_debug & SMIC_DEBUG_ENABLE)
			pr_warn("ipmi_smic_drv: smic hosed: %s\n", reason);
		smic->state = SMIC_HOSED;
	} else {
		smic->write_count = smic->orig_write_count;
		smic->write_pos = 0;
		smic->read_pos = 0;
		smic->state = SMIC_START_OP;
		smic->smic_timeout = SMIC_RETRY_TIMEOUT;
	}
}