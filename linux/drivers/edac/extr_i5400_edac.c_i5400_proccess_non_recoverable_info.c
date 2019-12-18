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
struct mem_ctl_info {int dummy; } ;
struct i5400_error_info {int /*<<< orphan*/  ferr_fat_fbd; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  enum hw_event_mc_err_type { ____Placeholder_hw_event_mc_err_type } hw_event_mc_err_type ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDAC_MC_LABEL_LEN ; 
 unsigned long ERROR_FAT_MASK ; 
 unsigned long FERR_NF_UNCORRECTABLE ; 
 int HW_EVENT_ERR_FATAL ; 
 int HW_EVENT_ERR_UNCORRECTED ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  edac_mc_handle_error (int,struct mem_ctl_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,char*,char*) ; 
 int /*<<< orphan*/ * error_name ; 
 int extract_fbdchan_indx (int /*<<< orphan*/ ) ; 
 int find_first_bit (unsigned long*,int /*<<< orphan*/ ) ; 
 int nrec_bank (struct i5400_error_info*) ; 
 int nrec_buf_id (struct i5400_error_info*) ; 
 int nrec_cas (struct i5400_error_info*) ; 
 int nrec_rank (struct i5400_error_info*) ; 
 int nrec_ras (struct i5400_error_info*) ; 
 int nrec_rdwr (struct i5400_error_info*) ; 
 int /*<<< orphan*/  rdwr_str (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i5400_proccess_non_recoverable_info(struct mem_ctl_info *mci,
				    struct i5400_error_info *info,
				    unsigned long allErrors)
{
	char msg[EDAC_MC_LABEL_LEN + 1 + 90 + 80];
	int branch;
	int channel;
	int bank;
	int buf_id;
	int rank;
	int rdwr;
	int ras, cas;
	int errnum;
	char *type = NULL;
	enum hw_event_mc_err_type tp_event = HW_EVENT_ERR_UNCORRECTED;

	if (!allErrors)
		return;		/* if no error, return now */

	if (allErrors &  ERROR_FAT_MASK) {
		type = "FATAL";
		tp_event = HW_EVENT_ERR_FATAL;
	} else if (allErrors & FERR_NF_UNCORRECTABLE)
		type = "NON-FATAL uncorrected";
	else
		type = "NON-FATAL recoverable";

	/* ONLY ONE of the possible error bits will be set, as per the docs */

	branch = extract_fbdchan_indx(info->ferr_fat_fbd);
	channel = branch;

	/* Use the NON-Recoverable macros to extract data */
	bank = nrec_bank(info);
	rank = nrec_rank(info);
	buf_id = nrec_buf_id(info);
	rdwr = nrec_rdwr(info);
	ras = nrec_ras(info);
	cas = nrec_cas(info);

	edac_dbg(0, "\t\tDIMM= %d  Channels= %d,%d  (Branch= %d DRAM Bank= %d Buffer ID = %d rdwr= %s ras= %d cas= %d)\n",
		 rank, channel, channel + 1, branch >> 1, bank,
		 buf_id, rdwr_str(rdwr), ras, cas);

	/* Only 1 bit will be on */
	errnum = find_first_bit(&allErrors, ARRAY_SIZE(error_name));

	/* Form out message */
	snprintf(msg, sizeof(msg),
		 "Bank=%d Buffer ID = %d RAS=%d CAS=%d Err=0x%lx (%s)",
		 bank, buf_id, ras, cas, allErrors, error_name[errnum]);

	edac_mc_handle_error(tp_event, mci, 1, 0, 0, 0,
			     branch >> 1, -1, rank,
			     rdwr ? "Write error" : "Read error",
			     msg);
}