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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CONFIG ; 
 int CPU_CONFIG_DC_PREF ; 
 int CPU_CONFIG_IC_PREF ; 
 int /*<<< orphan*/  CPU_CONTROL ; 
 int CPU_CONTROL_L2_MODE ; 
 int CPU_CONTROL_L2_SIZE ; 
 int /*<<< orphan*/  CPU_L2_CONFIG ; 
 int CPU_L2_CONFIG_MODE ; 
#define  MV_DEV_88F5181 144 
#define  MV_DEV_88F5182 143 
#define  MV_DEV_88F5281 142 
#define  MV_DEV_88F6281 141 
#define  MV_DEV_88F6282 140 
#define  MV_DEV_88F6781 139 
#define  MV_DEV_88F6810 138 
#define  MV_DEV_88F6820 137 
#define  MV_DEV_88F6828 136 
#define  MV_DEV_88RC8180 135 
#define  MV_DEV_88RC9480 134 
#define  MV_DEV_88RC9580 133 
#define  MV_DEV_MV78100 132 
#define  MV_DEV_MV78100_Z0 131 
#define  MV_DEV_MV78160 130 
#define  MV_DEV_MV78260 129 
#define  MV_DEV_MV78460 128 
 scalar_t__ bootverbose ; 
 int get_cpu_freq () ; 
 int get_tclk () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_cpu_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
soc_identify(uint32_t d, uint32_t r)
{
	uint32_t size, mode, freq;
	const char *dev;
	const char *rev;

	printf("SOC: ");
	if (bootverbose)
		printf("(0x%4x:0x%02x) ", d, r);

	rev = "";
	switch (d) {
	case MV_DEV_88F5181:
		dev = "Marvell 88F5181";
		if (r == 3)
			rev = "B1";
		break;
	case MV_DEV_88F5182:
		dev = "Marvell 88F5182";
		if (r == 2)
			rev = "A2";
		break;
	case MV_DEV_88F5281:
		dev = "Marvell 88F5281";
		if (r == 4)
			rev = "D0";
		else if (r == 5)
			rev = "D1";
		else if (r == 6)
			rev = "D2";
		break;
	case MV_DEV_88F6281:
		dev = "Marvell 88F6281";
		if (r == 0)
			rev = "Z0";
		else if (r == 2)
			rev = "A0";
		else if (r == 3)
			rev = "A1";
		break;
	case MV_DEV_88RC8180:
		dev = "Marvell 88RC8180";
		break;
	case MV_DEV_88RC9480:
		dev = "Marvell 88RC9480";
		break;
	case MV_DEV_88RC9580:
		dev = "Marvell 88RC9580";
		break;
	case MV_DEV_88F6781:
		dev = "Marvell 88F6781";
		if (r == 2)
			rev = "Y0";
		break;
	case MV_DEV_88F6282:
		dev = "Marvell 88F6282";
		if (r == 0)
			rev = "A0";
		else if (r == 1)
			rev = "A1";
		break;
	case MV_DEV_88F6828:
		dev = "Marvell 88F6828";
		break;
	case MV_DEV_88F6820:
		dev = "Marvell 88F6820";
		break;
	case MV_DEV_88F6810:
		dev = "Marvell 88F6810";
		break;
	case MV_DEV_MV78100_Z0:
		dev = "Marvell MV78100 Z0";
		break;
	case MV_DEV_MV78100:
		dev = "Marvell MV78100";
		break;
	case MV_DEV_MV78160:
		dev = "Marvell MV78160";
		break;
	case MV_DEV_MV78260:
		dev = "Marvell MV78260";
		break;
	case MV_DEV_MV78460:
		dev = "Marvell MV78460";
		break;
	default:
		dev = "UNKNOWN";
		break;
	}

	printf("%s", dev);
	if (*rev != '\0')
		printf(" rev %s", rev);
	printf(", TClock %dMHz", get_tclk() / 1000 / 1000);
	freq = get_cpu_freq();
	if (freq != 0)
		printf(", Frequency %dMHz", freq / 1000 / 1000);
	printf("\n");

	mode = read_cpu_ctrl(CPU_CONFIG);
	printf("  Instruction cache prefetch %s, data cache prefetch %s\n",
	    (mode & CPU_CONFIG_IC_PREF) ? "enabled" : "disabled",
	    (mode & CPU_CONFIG_DC_PREF) ? "enabled" : "disabled");

	switch (d) {
	case MV_DEV_88F6281:
	case MV_DEV_88F6282:
		mode = read_cpu_ctrl(CPU_L2_CONFIG) & CPU_L2_CONFIG_MODE;
		printf("  256KB 4-way set-associative %s unified L2 cache\n",
		    mode ? "write-through" : "write-back");
		break;
	case MV_DEV_MV78100:
		mode = read_cpu_ctrl(CPU_CONTROL);
		size = mode & CPU_CONTROL_L2_SIZE;
		mode = mode & CPU_CONTROL_L2_MODE;
		printf("  %s set-associative %s unified L2 cache\n",
		    size ? "256KB 4-way" : "512KB 8-way",
		    mode ? "write-through" : "write-back");
		break;
	default:
		break;
	}
}