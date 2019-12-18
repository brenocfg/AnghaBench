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
struct ppc4xx_edac_pdata {int /*<<< orphan*/  dcr_host; } ;
struct ppc4xx_ecc_status {int ecces; } ;
struct mem_ctl_info {struct ppc4xx_edac_pdata* pvt_info; } ;

/* Variables and functions */
#define  SDRAM_ECCES_CKBER_32_ECC_0_3 133 
#define  SDRAM_ECCES_CKBER_32_ECC_0_8 132 
#define  SDRAM_ECCES_CKBER_32_ECC_4_8 131 
 int SDRAM_ECCES_CKBER_MASK ; 
#define  SDRAM_ECCES_CKBER_NONE 130 
 int /*<<< orphan*/  SDRAM_MCOPT1 ; 
#define  SDRAM_MCOPT1_WDTH_16 129 
#define  SDRAM_MCOPT1_WDTH_32 128 
 int SDRAM_MCOPT1_WDTH_MASK ; 
 int mfsdram (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snprintf (char*,size_t,char*,char const*) ; 

__attribute__((used)) static int
ppc4xx_edac_generate_checkbit_message(const struct mem_ctl_info *mci,
				      const struct ppc4xx_ecc_status *status,
				      char *buffer,
				      size_t size)
{
	const struct ppc4xx_edac_pdata *pdata = mci->pvt_info;
	const char *ckber = NULL;

	switch (status->ecces & SDRAM_ECCES_CKBER_MASK) {
	case SDRAM_ECCES_CKBER_NONE:
		ckber = "None";
		break;
	case SDRAM_ECCES_CKBER_32_ECC_0_3:
		ckber = "ECC0:3";
		break;
	case SDRAM_ECCES_CKBER_32_ECC_4_8:
		switch (mfsdram(&pdata->dcr_host, SDRAM_MCOPT1) &
			SDRAM_MCOPT1_WDTH_MASK) {
		case SDRAM_MCOPT1_WDTH_16:
			ckber = "ECC0:3";
			break;
		case SDRAM_MCOPT1_WDTH_32:
			ckber = "ECC4:8";
			break;
		default:
			ckber = "Unknown";
			break;
		}
		break;
	case SDRAM_ECCES_CKBER_32_ECC_0_8:
		ckber = "ECC0:8";
		break;
	default:
		ckber = "Unknown";
		break;
	}

	return snprintf(buffer, size, "Checkbit Error: %s", ckber);
}