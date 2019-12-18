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
typedef  int vm_offset_t ;
typedef  int uint32_t ;
typedef  scalar_t__ u_int ;

/* Variables and functions */
#define  HWSOC_MX6DL 132 
#define  HWSOC_MX6Q 131 
#define  HWSOC_MX6SL 130 
#define  HWSOC_MX6SOLO 129 
#define  HWSOC_MX6UL 128 
 int /*<<< orphan*/  IMX6_ANALOG_DIGPROG ; 
 int /*<<< orphan*/  IMX6_ANALOG_DIGPROG_SL ; 
 int IMX6_ANALOG_DIGPROG_SOCTYPE_MASK ; 
 int IMX6_ANALOG_DIGPROG_SOCTYPE_SHIFT ; 
 scalar_t__ IMXSOC_6DL ; 
 scalar_t__ IMXSOC_6Q ; 
 scalar_t__ IMXSOC_6S ; 
 scalar_t__ IMXSOC_6SL ; 
 scalar_t__ IMXSOC_6UL ; 
 int* devmap_ptov (int const,int) ; 
 int imx6_anatop_read_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

u_int
imx_soc_type(void)
{
	uint32_t digprog, hwsoc;
	uint32_t *pcr;
	static u_int soctype;
	const vm_offset_t SCU_CONFIG_PHYSADDR = 0x00a00004;
#define	HWSOC_MX6SL	0x60
#define	HWSOC_MX6DL	0x61
#define	HWSOC_MX6SOLO	0x62
#define	HWSOC_MX6Q	0x63
#define	HWSOC_MX6UL	0x64

	if (soctype != 0)
		return (soctype);

	digprog = imx6_anatop_read_4(IMX6_ANALOG_DIGPROG_SL);
	hwsoc = (digprog >> IMX6_ANALOG_DIGPROG_SOCTYPE_SHIFT) & 
	    IMX6_ANALOG_DIGPROG_SOCTYPE_MASK;

	if (hwsoc != HWSOC_MX6SL) {
		digprog = imx6_anatop_read_4(IMX6_ANALOG_DIGPROG);
		hwsoc = (digprog & IMX6_ANALOG_DIGPROG_SOCTYPE_MASK) >>
		    IMX6_ANALOG_DIGPROG_SOCTYPE_SHIFT;
		/*printf("digprog = 0x%08x\n", digprog);*/
		if (hwsoc == HWSOC_MX6DL) {
			pcr = devmap_ptov(SCU_CONFIG_PHYSADDR, 4);
			if (pcr != NULL) {
				/*printf("scu config = 0x%08x\n", *pcr);*/
				if ((*pcr & 0x03) == 0) {
					hwsoc = HWSOC_MX6SOLO;
				}
			}
		}
	}
	/* printf("hwsoc 0x%08x\n", hwsoc); */

	switch (hwsoc) {
	case HWSOC_MX6SL:
		soctype = IMXSOC_6SL;
		break;
	case HWSOC_MX6SOLO:
		soctype = IMXSOC_6S;
		break;
	case HWSOC_MX6DL:
		soctype = IMXSOC_6DL;
		break;
	case HWSOC_MX6Q :
		soctype = IMXSOC_6Q;
		break;
	case HWSOC_MX6UL:
		soctype = IMXSOC_6UL;
		break;
	default:
		printf("imx_soc_type: Don't understand hwsoc 0x%02x, "
		    "digprog 0x%08x; assuming IMXSOC_6Q\n", hwsoc, digprog);
		soctype = IMXSOC_6Q;
		break;
	}

	return (soctype);
}