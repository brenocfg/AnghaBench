#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct mem_ctl_info {int /*<<< orphan*/  n_layers; int /*<<< orphan*/  dimms; int /*<<< orphan*/  layers; struct i7core_pvt* pvt_info; } ;
struct TYPE_5__ {int mc_control; int mc_status; int max_dod; int ch_map; } ;
struct i7core_pvt {TYPE_1__* i7core_dev; TYPE_3__* channel; TYPE_2__ info; struct pci_dev*** pci_ch; struct pci_dev** pci_mcr; } ;
struct dimm_info {int nr_pages; int grain; int edac_mode; int mtype; int /*<<< orphan*/  label; int /*<<< orphan*/  dtype; } ;
typedef  enum mem_type { ____Placeholder_mem_type } mem_type ;
typedef  enum edac_type { ____Placeholder_edac_type } edac_type ;
struct TYPE_6__ {int is_3dimms_present; int is_single_4rank; int has_4rank; } ;
struct TYPE_4__ {int socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_ACTIVE (struct i7core_pvt*,int) ; 
 scalar_t__ CH_DISABLED (struct i7core_pvt*,int) ; 
 int /*<<< orphan*/  DEV_UNKNOWN ; 
 int /*<<< orphan*/  DEV_X16 ; 
 int /*<<< orphan*/  DEV_X4 ; 
 int /*<<< orphan*/  DEV_X8 ; 
 int /*<<< orphan*/  DIMM_PRESENT (int) ; 
 scalar_t__ ECC_ENABLED (struct i7core_pvt*) ; 
 scalar_t__ ECCx8 (struct i7core_pvt*) ; 
 struct dimm_info* EDAC_DIMM_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int EDAC_NONE ; 
 int EDAC_S4ECD4ED ; 
 int EDAC_S8ECD8ED ; 
 int ENODEV ; 
 int /*<<< orphan*/  MC_CHANNEL_DIMM_INIT_PARAMS ; 
 int /*<<< orphan*/  MC_CHANNEL_MAPPER ; 
 int /*<<< orphan*/  MC_CONTROL ; 
 int /*<<< orphan*/  MC_DOD_CH_DIMM0 ; 
 int /*<<< orphan*/  MC_DOD_CH_DIMM1 ; 
 int /*<<< orphan*/  MC_DOD_CH_DIMM2 ; 
 int MC_DOD_NUMBANK (int) ; 
 int MC_DOD_NUMCOL (int) ; 
 int MC_DOD_NUMRANK (int) ; 
 int MC_DOD_NUMROW (int) ; 
 int /*<<< orphan*/  MC_MAX_DOD ; 
 int /*<<< orphan*/  MC_SAG_CH_0 ; 
 int /*<<< orphan*/  MC_SAG_CH_1 ; 
 int /*<<< orphan*/  MC_SAG_CH_2 ; 
 int /*<<< orphan*/  MC_SAG_CH_3 ; 
 int /*<<< orphan*/  MC_SAG_CH_4 ; 
 int /*<<< orphan*/  MC_SAG_CH_5 ; 
 int /*<<< orphan*/  MC_SAG_CH_6 ; 
 int /*<<< orphan*/  MC_SAG_CH_7 ; 
 int /*<<< orphan*/  MC_STATUS ; 
 int MEM_DDR3 ; 
 int MEM_RDDR3 ; 
 int MiB_TO_PAGES (int) ; 
 int NUM_CHANS ; 
 int QUAD_RANK_PRESENT ; 
 int /*<<< orphan*/  RANKOFFSET (int) ; 
 int /*<<< orphan*/  RDLCH (int,int) ; 
 int REGISTERED_DIMM ; 
 int SINGLE_QUAD_RANK_PRESENT ; 
 int THREE_DIMMS_PRESENT ; 
 int /*<<< orphan*/  WRLCH (int,int) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,...) ; 
 int numbank (int) ; 
 int numcol (int) ; 
 int /*<<< orphan*/  numdimms (int) ; 
 int numrank (int) ; 
 int numrow (int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 

__attribute__((used)) static int get_dimm_config(struct mem_ctl_info *mci)
{
	struct i7core_pvt *pvt = mci->pvt_info;
	struct pci_dev *pdev;
	int i, j;
	enum edac_type mode;
	enum mem_type mtype;
	struct dimm_info *dimm;

	/* Get data from the MC register, function 0 */
	pdev = pvt->pci_mcr[0];
	if (!pdev)
		return -ENODEV;

	/* Device 3 function 0 reads */
	pci_read_config_dword(pdev, MC_CONTROL, &pvt->info.mc_control);
	pci_read_config_dword(pdev, MC_STATUS, &pvt->info.mc_status);
	pci_read_config_dword(pdev, MC_MAX_DOD, &pvt->info.max_dod);
	pci_read_config_dword(pdev, MC_CHANNEL_MAPPER, &pvt->info.ch_map);

	edac_dbg(0, "QPI %d control=0x%08x status=0x%08x dod=0x%08x map=0x%08x\n",
		 pvt->i7core_dev->socket, pvt->info.mc_control,
		 pvt->info.mc_status, pvt->info.max_dod, pvt->info.ch_map);

	if (ECC_ENABLED(pvt)) {
		edac_dbg(0, "ECC enabled with x%d SDCC\n", ECCx8(pvt) ? 8 : 4);
		if (ECCx8(pvt))
			mode = EDAC_S8ECD8ED;
		else
			mode = EDAC_S4ECD4ED;
	} else {
		edac_dbg(0, "ECC disabled\n");
		mode = EDAC_NONE;
	}

	/* FIXME: need to handle the error codes */
	edac_dbg(0, "DOD Max limits: DIMMS: %d, %d-ranked, %d-banked x%x x 0x%x\n",
		 numdimms(pvt->info.max_dod),
		 numrank(pvt->info.max_dod >> 2),
		 numbank(pvt->info.max_dod >> 4),
		 numrow(pvt->info.max_dod >> 6),
		 numcol(pvt->info.max_dod >> 9));

	for (i = 0; i < NUM_CHANS; i++) {
		u32 data, dimm_dod[3], value[8];

		if (!pvt->pci_ch[i][0])
			continue;

		if (!CH_ACTIVE(pvt, i)) {
			edac_dbg(0, "Channel %i is not active\n", i);
			continue;
		}
		if (CH_DISABLED(pvt, i)) {
			edac_dbg(0, "Channel %i is disabled\n", i);
			continue;
		}

		/* Devices 4-6 function 0 */
		pci_read_config_dword(pvt->pci_ch[i][0],
				MC_CHANNEL_DIMM_INIT_PARAMS, &data);


		if (data & THREE_DIMMS_PRESENT)
			pvt->channel[i].is_3dimms_present = true;

		if (data & SINGLE_QUAD_RANK_PRESENT)
			pvt->channel[i].is_single_4rank = true;

		if (data & QUAD_RANK_PRESENT)
			pvt->channel[i].has_4rank = true;

		if (data & REGISTERED_DIMM)
			mtype = MEM_RDDR3;
		else
			mtype = MEM_DDR3;

		/* Devices 4-6 function 1 */
		pci_read_config_dword(pvt->pci_ch[i][1],
				MC_DOD_CH_DIMM0, &dimm_dod[0]);
		pci_read_config_dword(pvt->pci_ch[i][1],
				MC_DOD_CH_DIMM1, &dimm_dod[1]);
		pci_read_config_dword(pvt->pci_ch[i][1],
				MC_DOD_CH_DIMM2, &dimm_dod[2]);

		edac_dbg(0, "Ch%d phy rd%d, wr%d (0x%08x): %s%s%s%cDIMMs\n",
			 i,
			 RDLCH(pvt->info.ch_map, i), WRLCH(pvt->info.ch_map, i),
			 data,
			 pvt->channel[i].is_3dimms_present ? "3DIMMS " : "",
			 pvt->channel[i].is_3dimms_present ? "SINGLE_4R " : "",
			 pvt->channel[i].has_4rank ? "HAS_4R " : "",
			 (data & REGISTERED_DIMM) ? 'R' : 'U');

		for (j = 0; j < 3; j++) {
			u32 banks, ranks, rows, cols;
			u32 size, npages;

			if (!DIMM_PRESENT(dimm_dod[j]))
				continue;

			dimm = EDAC_DIMM_PTR(mci->layers, mci->dimms, mci->n_layers,
				       i, j, 0);
			banks = numbank(MC_DOD_NUMBANK(dimm_dod[j]));
			ranks = numrank(MC_DOD_NUMRANK(dimm_dod[j]));
			rows = numrow(MC_DOD_NUMROW(dimm_dod[j]));
			cols = numcol(MC_DOD_NUMCOL(dimm_dod[j]));

			/* DDR3 has 8 I/O banks */
			size = (rows * cols * banks * ranks) >> (20 - 3);

			edac_dbg(0, "\tdimm %d %d MiB offset: %x, bank: %d, rank: %d, row: %#x, col: %#x\n",
				 j, size,
				 RANKOFFSET(dimm_dod[j]),
				 banks, ranks, rows, cols);

			npages = MiB_TO_PAGES(size);

			dimm->nr_pages = npages;

			switch (banks) {
			case 4:
				dimm->dtype = DEV_X4;
				break;
			case 8:
				dimm->dtype = DEV_X8;
				break;
			case 16:
				dimm->dtype = DEV_X16;
				break;
			default:
				dimm->dtype = DEV_UNKNOWN;
			}

			snprintf(dimm->label, sizeof(dimm->label),
				 "CPU#%uChannel#%u_DIMM#%u",
				 pvt->i7core_dev->socket, i, j);
			dimm->grain = 8;
			dimm->edac_mode = mode;
			dimm->mtype = mtype;
		}

		pci_read_config_dword(pdev, MC_SAG_CH_0, &value[0]);
		pci_read_config_dword(pdev, MC_SAG_CH_1, &value[1]);
		pci_read_config_dword(pdev, MC_SAG_CH_2, &value[2]);
		pci_read_config_dword(pdev, MC_SAG_CH_3, &value[3]);
		pci_read_config_dword(pdev, MC_SAG_CH_4, &value[4]);
		pci_read_config_dword(pdev, MC_SAG_CH_5, &value[5]);
		pci_read_config_dword(pdev, MC_SAG_CH_6, &value[6]);
		pci_read_config_dword(pdev, MC_SAG_CH_7, &value[7]);
		edac_dbg(1, "\t[%i] DIVBY3\tREMOVED\tOFFSET\n", i);
		for (j = 0; j < 8; j++)
			edac_dbg(1, "\t\t%#x\t%#x\t%#x\n",
				 (value[j] >> 27) & 0x1,
				 (value[j] >> 24) & 0x7,
				 (value[j] & ((1 << 24) - 1)));
	}

	return 0;
}