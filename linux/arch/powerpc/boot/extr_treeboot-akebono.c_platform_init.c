#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {char* cmdline; int cmdline_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  exit; int /*<<< orphan*/  fixups; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_PIR ; 
 int USERDATA_LEN ; 
 int /*<<< orphan*/  _dtb_start ; 
 scalar_t__ _end ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ fdt_check_header (int /*<<< orphan*/ ) ; 
 int* fdt_getprop (int /*<<< orphan*/ ,int,char*,int*) ; 
 int /*<<< orphan*/  fdt_init (int /*<<< orphan*/ ) ; 
 int fdt_node_offset_by_prop_value (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  fdt_set_boot_cpuid_phys (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ibm44x_dbcr_reset ; 
 int ibm_akebono_detect_memsize () ; 
 int /*<<< orphan*/  ibm_akebono_fixups ; 
 int ibm_akebono_memsize ; 
 TYPE_2__ loader_info ; 
 int /*<<< orphan*/  mac_addr ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 TYPE_1__ platform_ops ; 
 int /*<<< orphan*/  serial_console_init () ; 
 int /*<<< orphan*/  simple_alloc_init (scalar_t__,unsigned long,int,int) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strtoull (char*,char**,int) ; 
 int timebase_period_ns ; 

void platform_init(char *userdata)
{
	unsigned long end_of_ram, avail_ram;
	u32 pir_reg;
	int node, size;
	const u32 *timebase;
	int len, i, userdata_len;
	char *end;

	userdata[USERDATA_LEN - 1] = '\0';
	userdata_len = strlen(userdata);
	for (i = 0; i < userdata_len - 15; i++) {
		if (strncmp(&userdata[i], "local-mac-addr=", 15) == 0) {
			if (i > 0 && userdata[i - 1] != ' ') {
				/* We've only found a substring ending
				 * with local-mac-addr so this isn't
				 * our mac address. */
				continue;
			}

			mac_addr = strtoull(&userdata[i + 15], &end, 16);

			/* Remove the "local-mac-addr=<...>" from the kernel
			 * command line, including the tailing space if
			 * present. */
			if (*end == ' ')
				end++;

			len = ((int) end) - ((int) &userdata[i]);
			memmove(&userdata[i], end,
				userdata_len - (len + i) + 1);
			break;
		}
	}

	loader_info.cmdline = userdata;
	loader_info.cmdline_len = 256;

	ibm_akebono_memsize = ibm_akebono_detect_memsize();
	if (ibm_akebono_memsize >> 32)
		end_of_ram = ~0UL;
	else
		end_of_ram = ibm_akebono_memsize;
	avail_ram = end_of_ram - (unsigned long)_end;

	simple_alloc_init(_end, avail_ram, 128, 64);
	platform_ops.fixups = ibm_akebono_fixups;
	platform_ops.exit = ibm44x_dbcr_reset;
	pir_reg = mfspr(SPRN_PIR);

	/* Make sure FDT blob is sane */
	if (fdt_check_header(_dtb_start) != 0)
		fatal("Invalid device tree blob\n");

	node = fdt_node_offset_by_prop_value(_dtb_start, -1, "device_type",
					     "cpu", sizeof("cpu"));
	if (!node)
		fatal("Cannot find cpu node\n");
	timebase = fdt_getprop(_dtb_start, node, "timebase-frequency", &size);
	if (timebase && (size == 4))
		timebase_period_ns = 1000000000 / *timebase;

	fdt_set_boot_cpuid_phys(_dtb_start, pir_reg);
	fdt_init(_dtb_start);

	serial_console_init();
}