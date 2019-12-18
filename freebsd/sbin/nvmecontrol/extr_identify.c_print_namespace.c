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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct nvme_namespace_data {int nsfeat; int flbas; int nlbaf; int dpc; int dps; int nmic; int rescap; int fpi; int dlfeat; int noiob; int npwg; int npwa; int npdg; int npda; int nows; int* nguid; int* eui64; int* lbaf; int /*<<< orphan*/  nvmcap; scalar_t__ nuse; scalar_t__ ncap; scalar_t__ nsze; } ;
typedef  int /*<<< orphan*/  cbuf ;

/* Variables and functions */
 int NVME_NS_DATA_DLFEAT_DWZ_MASK ; 
 int NVME_NS_DATA_DLFEAT_DWZ_SHIFT ; 
 int NVME_NS_DATA_DLFEAT_GCRC_MASK ; 
 int NVME_NS_DATA_DLFEAT_GCRC_SHIFT ; 
 int NVME_NS_DATA_DLFEAT_READ_00 ; 
 int NVME_NS_DATA_DLFEAT_READ_FF ; 
 int NVME_NS_DATA_DLFEAT_READ_MASK ; 
 int NVME_NS_DATA_DLFEAT_READ_NR ; 
 int NVME_NS_DATA_DLFEAT_READ_SHIFT ; 
 int NVME_NS_DATA_DPC_MD_END_MASK ; 
 int NVME_NS_DATA_DPC_MD_END_SHIFT ; 
 int NVME_NS_DATA_DPC_MD_START_MASK ; 
 int NVME_NS_DATA_DPC_MD_START_SHIFT ; 
 int NVME_NS_DATA_DPC_PIT1_MASK ; 
 int NVME_NS_DATA_DPC_PIT2_MASK ; 
 int NVME_NS_DATA_DPC_PIT2_SHIFT ; 
 int NVME_NS_DATA_DPC_PIT3_MASK ; 
 int NVME_NS_DATA_DPC_PIT3_SHIFT ; 
 int NVME_NS_DATA_DPS_MD_START_MASK ; 
 int NVME_NS_DATA_DPS_MD_START_SHIFT ; 
 int NVME_NS_DATA_DPS_PIT_MASK ; 
 int NVME_NS_DATA_DPS_PIT_SHIFT ; 
 int NVME_NS_DATA_FLBAS_FORMAT_MASK ; 
 int NVME_NS_DATA_FLBAS_FORMAT_SHIFT ; 
 int NVME_NS_DATA_FPI_PERC_MASK ; 
 int NVME_NS_DATA_FPI_PERC_SHIFT ; 
 int NVME_NS_DATA_FPI_SUPP_MASK ; 
 int NVME_NS_DATA_FPI_SUPP_SHIFT ; 
 int NVME_NS_DATA_LBAF_LBADS_MASK ; 
 int NVME_NS_DATA_LBAF_LBADS_SHIFT ; 
 int NVME_NS_DATA_LBAF_MS_MASK ; 
 int NVME_NS_DATA_LBAF_MS_SHIFT ; 
 int NVME_NS_DATA_LBAF_RP_MASK ; 
 int NVME_NS_DATA_LBAF_RP_SHIFT ; 
 int NVME_NS_DATA_NMIC_MAY_BE_SHARED_MASK ; 
 int NVME_NS_DATA_NMIC_MAY_BE_SHARED_SHIFT ; 
 int NVME_NS_DATA_NSFEAT_NPVALID_MASK ; 
 int NVME_NS_DATA_NSFEAT_NPVALID_SHIFT ; 
 int NVME_NS_DATA_NSFEAT_THIN_PROV_MASK ; 
 int NVME_NS_DATA_NSFEAT_THIN_PROV_SHIFT ; 
 int NVME_NS_DATA_RESCAP_EX_AC_AR_MASK ; 
 int NVME_NS_DATA_RESCAP_EX_AC_AR_SHIFT ; 
 int NVME_NS_DATA_RESCAP_EX_AC_MASK ; 
 int NVME_NS_DATA_RESCAP_EX_AC_RO_MASK ; 
 int NVME_NS_DATA_RESCAP_EX_AC_RO_SHIFT ; 
 int NVME_NS_DATA_RESCAP_EX_AC_SHIFT ; 
 int NVME_NS_DATA_RESCAP_IEKEY13_MASK ; 
 int NVME_NS_DATA_RESCAP_IEKEY13_SHIFT ; 
 int NVME_NS_DATA_RESCAP_PTPL_MASK ; 
 int NVME_NS_DATA_RESCAP_PTPL_SHIFT ; 
 int NVME_NS_DATA_RESCAP_WR_EX_AR_MASK ; 
 int NVME_NS_DATA_RESCAP_WR_EX_AR_SHIFT ; 
 int NVME_NS_DATA_RESCAP_WR_EX_MASK ; 
 int NVME_NS_DATA_RESCAP_WR_EX_RO_MASK ; 
 int NVME_NS_DATA_RESCAP_WR_EX_RO_SHIFT ; 
 int NVME_NS_DATA_RESCAP_WR_EX_SHIFT ; 
 int /*<<< orphan*/  UINT128_DIG ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  to128 (int /*<<< orphan*/ ) ; 
 char* uint128_to_str (int /*<<< orphan*/ ,char*,int) ; 

void
print_namespace(struct nvme_namespace_data *nsdata)
{
	char cbuf[UINT128_DIG + 1];
	uint32_t	i;
	uint32_t	lbaf, lbads, ms, rp;
	uint8_t		thin_prov, ptype;
	uint8_t		flbas_fmt, t;

	thin_prov = (nsdata->nsfeat >> NVME_NS_DATA_NSFEAT_THIN_PROV_SHIFT) &
		NVME_NS_DATA_NSFEAT_THIN_PROV_MASK;

	flbas_fmt = (nsdata->flbas >> NVME_NS_DATA_FLBAS_FORMAT_SHIFT) &
		NVME_NS_DATA_FLBAS_FORMAT_MASK;

	printf("Size:                        %lld blocks\n",
	    (long long)nsdata->nsze);
	printf("Capacity:                    %lld blocks\n",
	    (long long)nsdata->ncap);
	printf("Utilization:                 %lld blocks\n",
	    (long long)nsdata->nuse);
	printf("Thin Provisioning:           %s\n",
		thin_prov ? "Supported" : "Not Supported");
	printf("Number of LBA Formats:       %d\n", nsdata->nlbaf+1);
	printf("Current LBA Format:          LBA Format #%02d\n", flbas_fmt);
	printf("Data Protection Caps:        %s%s%s%s%s%s\n",
	    (nsdata->dpc == 0) ? "Not Supported" : "",
	    ((nsdata->dpc >> NVME_NS_DATA_DPC_MD_END_SHIFT) &
	     NVME_NS_DATA_DPC_MD_END_MASK) ? "Last Bytes, " : "",
	    ((nsdata->dpc >> NVME_NS_DATA_DPC_MD_START_SHIFT) &
	     NVME_NS_DATA_DPC_MD_START_MASK) ? "First Bytes, " : "",
	    ((nsdata->dpc >> NVME_NS_DATA_DPC_PIT3_SHIFT) &
	     NVME_NS_DATA_DPC_PIT3_MASK) ? "Type 3, " : "",
	    ((nsdata->dpc >> NVME_NS_DATA_DPC_PIT2_SHIFT) &
	     NVME_NS_DATA_DPC_PIT2_MASK) ? "Type 2, " : "",
	    ((nsdata->dpc >> NVME_NS_DATA_DPC_PIT2_MASK) &
	     NVME_NS_DATA_DPC_PIT1_MASK) ? "Type 1" : "");
	printf("Data Protection Settings:    ");
	ptype = (nsdata->dps >> NVME_NS_DATA_DPS_PIT_SHIFT) &
	    NVME_NS_DATA_DPS_PIT_MASK;
	if (ptype) {
		printf("Type %d, %s Bytes\n", ptype,
		    ((nsdata->dps >> NVME_NS_DATA_DPS_MD_START_SHIFT) &
		     NVME_NS_DATA_DPS_MD_START_MASK) ? "First" : "Last");
	} else {
		printf("Not Enabled\n");
	}
	printf("Multi-Path I/O Capabilities: %s%s\n",
	    (nsdata->nmic == 0) ? "Not Supported" : "",
	    ((nsdata->nmic >> NVME_NS_DATA_NMIC_MAY_BE_SHARED_SHIFT) &
	     NVME_NS_DATA_NMIC_MAY_BE_SHARED_MASK) ? "May be shared" : "");
	printf("Reservation Capabilities:    %s%s%s%s%s%s%s%s%s\n",
	    (nsdata->rescap == 0) ? "Not Supported" : "",
	    ((nsdata->rescap >> NVME_NS_DATA_RESCAP_IEKEY13_SHIFT) &
	     NVME_NS_DATA_RESCAP_IEKEY13_MASK) ? "IEKEY13, " : "",
	    ((nsdata->rescap >> NVME_NS_DATA_RESCAP_EX_AC_AR_SHIFT) &
	     NVME_NS_DATA_RESCAP_EX_AC_AR_MASK) ? "EX_AC_AR, " : "",
	    ((nsdata->rescap >> NVME_NS_DATA_RESCAP_WR_EX_AR_SHIFT) &
	     NVME_NS_DATA_RESCAP_WR_EX_AR_MASK) ? "WR_EX_AR, " : "",
	    ((nsdata->rescap >> NVME_NS_DATA_RESCAP_EX_AC_RO_SHIFT) &
	     NVME_NS_DATA_RESCAP_EX_AC_RO_MASK) ? "EX_AC_RO, " : "",
	    ((nsdata->rescap >> NVME_NS_DATA_RESCAP_WR_EX_RO_SHIFT) &
	     NVME_NS_DATA_RESCAP_WR_EX_RO_MASK) ? "WR_EX_RO, " : "",
	    ((nsdata->rescap >> NVME_NS_DATA_RESCAP_EX_AC_SHIFT) &
	     NVME_NS_DATA_RESCAP_EX_AC_MASK) ? "EX_AC, " : "",
	    ((nsdata->rescap >> NVME_NS_DATA_RESCAP_WR_EX_SHIFT) &
	     NVME_NS_DATA_RESCAP_WR_EX_MASK) ? "WR_EX, " : "",
	    ((nsdata->rescap >> NVME_NS_DATA_RESCAP_PTPL_SHIFT) &
	     NVME_NS_DATA_RESCAP_PTPL_MASK) ? "PTPL" : "");
	printf("Format Progress Indicator:   ");
	if ((nsdata->fpi >> NVME_NS_DATA_FPI_SUPP_SHIFT) &
	    NVME_NS_DATA_FPI_SUPP_MASK) {
		printf("%u%% remains\n",
		    (nsdata->fpi >> NVME_NS_DATA_FPI_PERC_SHIFT) &
		    NVME_NS_DATA_FPI_PERC_MASK);
	} else
		printf("Not Supported\n");
	t = (nsdata->dlfeat >> NVME_NS_DATA_DLFEAT_READ_SHIFT) &
	    NVME_NS_DATA_DLFEAT_READ_MASK;
	printf("Deallocate Logical Block:    Read %s%s%s\n",
	    (t == NVME_NS_DATA_DLFEAT_READ_NR) ? "Not Reported" :
	    (t == NVME_NS_DATA_DLFEAT_READ_00) ? "00h" :
	    (t == NVME_NS_DATA_DLFEAT_READ_FF) ? "FFh" : "Unknown",
	    (nsdata->dlfeat >> NVME_NS_DATA_DLFEAT_DWZ_SHIFT) &
	     NVME_NS_DATA_DLFEAT_DWZ_MASK ? ", Write Zero" : "",
	    (nsdata->dlfeat >> NVME_NS_DATA_DLFEAT_GCRC_SHIFT) &
	     NVME_NS_DATA_DLFEAT_GCRC_MASK ? ", Guard CRC" : "");
	printf("Optimal I/O Boundary:        %u blocks\n", nsdata->noiob);
	printf("NVM Capacity:                %s bytes\n",
	   uint128_to_str(to128(nsdata->nvmcap), cbuf, sizeof(cbuf)));
	if ((nsdata->nsfeat >> NVME_NS_DATA_NSFEAT_NPVALID_SHIFT) &
	    NVME_NS_DATA_NSFEAT_NPVALID_MASK) {
		printf("Preferred Write Granularity: %u blocks",
		    nsdata->npwg + 1);
		printf("Preferred Write Alignment:   %u blocks",
		    nsdata->npwa + 1);
		printf("Preferred Deallocate Granul: %u blocks",
		    nsdata->npdg + 1);
		printf("Preferred Deallocate Align:  %u blocks",
		    nsdata->npda + 1);
		printf("Optimal Write Size:          %u blocks",
		    nsdata->nows + 1);
	}
	printf("Globally Unique Identifier:  ");
	for (i = 0; i < sizeof(nsdata->nguid); i++)
		printf("%02x", nsdata->nguid[i]);
	printf("\n");
	printf("IEEE EUI64:                  ");
	for (i = 0; i < sizeof(nsdata->eui64); i++)
		printf("%02x", nsdata->eui64[i]);
	printf("\n");
	for (i = 0; i <= nsdata->nlbaf; i++) {
		lbaf = nsdata->lbaf[i];
		lbads = (lbaf >> NVME_NS_DATA_LBAF_LBADS_SHIFT) &
			NVME_NS_DATA_LBAF_LBADS_MASK;
		ms = (lbaf >> NVME_NS_DATA_LBAF_MS_SHIFT) &
			NVME_NS_DATA_LBAF_MS_MASK;
		rp = (lbaf >> NVME_NS_DATA_LBAF_RP_SHIFT) &
			NVME_NS_DATA_LBAF_RP_MASK;
		printf("LBA Format #%02d: Data Size: %5d  Metadata Size: %5d"
		    "  Performance: %s\n",
		    i, 1 << lbads, ms, (rp == 0) ? "Best" :
		    (rp == 1) ? "Better" : (rp == 2) ? "Good" : "Degraded");
	}
}