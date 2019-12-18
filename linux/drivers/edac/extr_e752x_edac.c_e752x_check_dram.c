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
typedef  int u16 ;
struct mem_ctl_info {int dummy; } ;
struct e752x_error_info {int dram_ferr; int dram_nerr; int /*<<< orphan*/  dram_scrb_add; int /*<<< orphan*/  dram_ded_add; int /*<<< orphan*/  dram_retr_add; int /*<<< orphan*/  dram_sec2_syndrome; int /*<<< orphan*/  dram_sec2_add; int /*<<< orphan*/  dram_sec1_syndrome; int /*<<< orphan*/  dram_sec1_add; } ;

/* Variables and functions */
 int /*<<< orphan*/  process_ce (struct mem_ctl_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  process_ded_retry (struct mem_ctl_info*,int,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  process_threshold_ce (struct mem_ctl_info*,int,int*,int) ; 
 int /*<<< orphan*/  process_ue (struct mem_ctl_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  process_ue_no_info_wr (struct mem_ctl_info*,int*,int) ; 

__attribute__((used)) static void e752x_check_dram(struct mem_ctl_info *mci,
			struct e752x_error_info *info, int *error_found,
			int handle_error)
{
	u16 error_one, error_next;

	error_one = info->dram_ferr;
	error_next = info->dram_nerr;

	/* decode and report errors */
	if (error_one & 0x0101)	/* check first error correctable */
		process_ce(mci, error_one, info->dram_sec1_add,
			info->dram_sec1_syndrome, error_found, handle_error);

	if (error_next & 0x0101)	/* check next error correctable */
		process_ce(mci, error_next, info->dram_sec2_add,
			info->dram_sec2_syndrome, error_found, handle_error);

	if (error_one & 0x4040)
		process_ue_no_info_wr(mci, error_found, handle_error);

	if (error_next & 0x4040)
		process_ue_no_info_wr(mci, error_found, handle_error);

	if (error_one & 0x2020)
		process_ded_retry(mci, error_one, info->dram_retr_add,
				error_found, handle_error);

	if (error_next & 0x2020)
		process_ded_retry(mci, error_next, info->dram_retr_add,
				error_found, handle_error);

	if (error_one & 0x0808)
		process_threshold_ce(mci, error_one, error_found, handle_error);

	if (error_next & 0x0808)
		process_threshold_ce(mci, error_next, error_found,
				handle_error);

	if (error_one & 0x0606)
		process_ue(mci, error_one, info->dram_ded_add,
			info->dram_scrb_add, error_found, handle_error);

	if (error_next & 0x0606)
		process_ue(mci, error_next, info->dram_ded_add,
			info->dram_scrb_add, error_found, handle_error);
}