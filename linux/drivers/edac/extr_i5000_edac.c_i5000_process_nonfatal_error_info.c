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
typedef  int u32 ;
struct mem_ctl_info {int dummy; } ;
struct i5000_error_info {int ferr_nf_fbd; int /*<<< orphan*/  recmemb; int /*<<< orphan*/  recmema; int /*<<< orphan*/  redmemb; int /*<<< orphan*/  nrecmemb; int /*<<< orphan*/  nrecmema; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_MC_LABEL_LEN ; 
 int EXTRACT_FBDCHAN_INDX (int) ; 
 int FERR_NF_CORRECTABLE ; 
 int FERR_NF_DIMM_SPARE ; 
#define  FERR_NF_M10ERR 147 
#define  FERR_NF_M11ERR 146 
#define  FERR_NF_M12ERR 145 
#define  FERR_NF_M13ERR 144 
#define  FERR_NF_M14ERR 143 
#define  FERR_NF_M15ERR 142 
#define  FERR_NF_M17ERR 141 
#define  FERR_NF_M18ERR 140 
#define  FERR_NF_M19ERR 139 
#define  FERR_NF_M20ERR 138 
#define  FERR_NF_M21ERR 137 
#define  FERR_NF_M22ERR 136 
#define  FERR_NF_M27ERR 135 
#define  FERR_NF_M28ERR 134 
#define  FERR_NF_M4ERR 133 
#define  FERR_NF_M5ERR 132 
#define  FERR_NF_M6ERR 131 
#define  FERR_NF_M7ERR 130 
#define  FERR_NF_M8ERR 129 
#define  FERR_NF_M9ERR 128 
 int FERR_NF_MASK ; 
 int FERR_NF_NON_RETRY ; 
 int FERR_NF_NORTH_CRC ; 
 int FERR_NF_SPD_PROTOCOL ; 
 int FERR_NF_UNCORRECTABLE ; 
 int /*<<< orphan*/  HW_EVENT_ERR_CORRECTED ; 
 int /*<<< orphan*/  HW_EVENT_ERR_UNCORRECTED ; 
 int NREC_BANK (int /*<<< orphan*/ ) ; 
 int NREC_CAS (int /*<<< orphan*/ ) ; 
 int NREC_RANK (int /*<<< orphan*/ ) ; 
 int NREC_RAS (int /*<<< orphan*/ ) ; 
 int NREC_RDWR (int /*<<< orphan*/ ) ; 
 int REC_BANK (int /*<<< orphan*/ ) ; 
 int REC_CAS (int /*<<< orphan*/ ) ; 
 scalar_t__ REC_ECC_LOCATOR_ODD (int /*<<< orphan*/ ) ; 
 int REC_RANK (int /*<<< orphan*/ ) ; 
 int REC_RAS (int /*<<< orphan*/ ) ; 
 int REC_RDWR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,char*,char*) ; 
 int /*<<< orphan*/  misc_messages ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 

__attribute__((used)) static void i5000_process_nonfatal_error_info(struct mem_ctl_info *mci,
					struct i5000_error_info *info,
					int handle_errors)
{
	char msg[EDAC_MC_LABEL_LEN + 1 + 170];
	char *specific = NULL;
	u32 allErrors;
	u32 ue_errors;
	u32 ce_errors;
	u32 misc_errors;
	int branch;
	int channel;
	int bank;
	int rank;
	int rdwr;
	int ras, cas;

	/* mask off the Error bits that are possible */
	allErrors = (info->ferr_nf_fbd & FERR_NF_MASK);
	if (!allErrors)
		return;		/* if no error, return now */

	/* ONLY ONE of the possible error bits will be set, as per the docs */
	ue_errors = allErrors & FERR_NF_UNCORRECTABLE;
	if (ue_errors) {
		edac_dbg(0, "\tUncorrected bits= 0x%x\n", ue_errors);

		branch = EXTRACT_FBDCHAN_INDX(info->ferr_nf_fbd);

		/*
		 * According with i5000 datasheet, bit 28 has no significance
		 * for errors M4Err-M12Err and M17Err-M21Err, on FERR_NF_FBD
		 */
		channel = branch & 2;

		bank = NREC_BANK(info->nrecmema);
		rank = NREC_RANK(info->nrecmema);
		rdwr = NREC_RDWR(info->nrecmema);
		ras = NREC_RAS(info->nrecmemb);
		cas = NREC_CAS(info->nrecmemb);

		edac_dbg(0, "\t\tCSROW= %d  Channels= %d,%d  (Branch= %d DRAM Bank= %d rdwr= %s ras= %d cas= %d)\n",
			 rank, channel, channel + 1, branch >> 1, bank,
			 rdwr ? "Write" : "Read", ras, cas);

		switch (ue_errors) {
		case FERR_NF_M12ERR:
			specific = "Non-Aliased Uncorrectable Patrol Data ECC";
			break;
		case FERR_NF_M11ERR:
			specific = "Non-Aliased Uncorrectable Spare-Copy "
					"Data ECC";
			break;
		case FERR_NF_M10ERR:
			specific = "Non-Aliased Uncorrectable Mirrored Demand "
					"Data ECC";
			break;
		case FERR_NF_M9ERR:
			specific = "Non-Aliased Uncorrectable Non-Mirrored "
					"Demand Data ECC";
			break;
		case FERR_NF_M8ERR:
			specific = "Aliased Uncorrectable Patrol Data ECC";
			break;
		case FERR_NF_M7ERR:
			specific = "Aliased Uncorrectable Spare-Copy Data ECC";
			break;
		case FERR_NF_M6ERR:
			specific = "Aliased Uncorrectable Mirrored Demand "
					"Data ECC";
			break;
		case FERR_NF_M5ERR:
			specific = "Aliased Uncorrectable Non-Mirrored Demand "
					"Data ECC";
			break;
		case FERR_NF_M4ERR:
			specific = "Uncorrectable Data ECC on Replay";
			break;
		}

		/* Form out message */
		snprintf(msg, sizeof(msg),
			 "Rank=%d Bank=%d RAS=%d CAS=%d, UE Err=0x%x (%s)",
			 rank, bank, ras, cas, ue_errors, specific);

		/* Call the helper to output message */
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1, 0, 0, 0,
				channel >> 1, -1, rank,
				rdwr ? "Write error" : "Read error",
				msg);
	}

	/* Check correctable errors */
	ce_errors = allErrors & FERR_NF_CORRECTABLE;
	if (ce_errors) {
		edac_dbg(0, "\tCorrected bits= 0x%x\n", ce_errors);

		branch = EXTRACT_FBDCHAN_INDX(info->ferr_nf_fbd);

		channel = 0;
		if (REC_ECC_LOCATOR_ODD(info->redmemb))
			channel = 1;

		/* Convert channel to be based from zero, instead of
		 * from branch base of 0 */
		channel += branch;

		bank = REC_BANK(info->recmema);
		rank = REC_RANK(info->recmema);
		rdwr = REC_RDWR(info->recmema);
		ras = REC_RAS(info->recmemb);
		cas = REC_CAS(info->recmemb);

		edac_dbg(0, "\t\tCSROW= %d Channel= %d  (Branch %d DRAM Bank= %d rdwr= %s ras= %d cas= %d)\n",
			 rank, channel, branch >> 1, bank,
			 rdwr ? "Write" : "Read", ras, cas);

		switch (ce_errors) {
		case FERR_NF_M17ERR:
			specific = "Correctable Non-Mirrored Demand Data ECC";
			break;
		case FERR_NF_M18ERR:
			specific = "Correctable Mirrored Demand Data ECC";
			break;
		case FERR_NF_M19ERR:
			specific = "Correctable Spare-Copy Data ECC";
			break;
		case FERR_NF_M20ERR:
			specific = "Correctable Patrol Data ECC";
			break;
		}

		/* Form out message */
		snprintf(msg, sizeof(msg),
			 "Rank=%d Bank=%d RDWR=%s RAS=%d "
			 "CAS=%d, CE Err=0x%x (%s))", branch >> 1, bank,
			 rdwr ? "Write" : "Read", ras, cas, ce_errors,
			 specific);

		/* Call the helper to output message */
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1, 0, 0, 0,
				channel >> 1, channel % 2, rank,
				rdwr ? "Write error" : "Read error",
				msg);
	}

	if (!misc_messages)
		return;

	misc_errors = allErrors & (FERR_NF_NON_RETRY | FERR_NF_NORTH_CRC |
				   FERR_NF_SPD_PROTOCOL | FERR_NF_DIMM_SPARE);
	if (misc_errors) {
		switch (misc_errors) {
		case FERR_NF_M13ERR:
			specific = "Non-Retry or Redundant Retry FBD Memory "
					"Alert or Redundant Fast Reset Timeout";
			break;
		case FERR_NF_M14ERR:
			specific = "Non-Retry or Redundant Retry FBD "
					"Configuration Alert";
			break;
		case FERR_NF_M15ERR:
			specific = "Non-Retry or Redundant Retry FBD "
					"Northbound CRC error on read data";
			break;
		case FERR_NF_M21ERR:
			specific = "FBD Northbound CRC error on "
					"FBD Sync Status";
			break;
		case FERR_NF_M22ERR:
			specific = "SPD protocol error";
			break;
		case FERR_NF_M27ERR:
			specific = "DIMM-spare copy started";
			break;
		case FERR_NF_M28ERR:
			specific = "DIMM-spare copy completed";
			break;
		}
		branch = EXTRACT_FBDCHAN_INDX(info->ferr_nf_fbd);

		/* Form out message */
		snprintf(msg, sizeof(msg),
			 "Err=%#x (%s)", misc_errors, specific);

		/* Call the helper to output message */
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1, 0, 0, 0,
				branch >> 1, -1, -1,
				"Misc error", msg);
	}
}