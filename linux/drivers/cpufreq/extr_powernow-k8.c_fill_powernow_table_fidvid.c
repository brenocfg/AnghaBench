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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_4__ {int state_count; TYPE_1__* states; } ;
struct powernow_k8_data {TYPE_2__ acpi_data; scalar_t__ exttype; } ;
struct cpufreq_frequency_table {int driver_data; int frequency; } ;
struct TYPE_3__ {int status; int control; int core_frequency; } ;

/* Variables and functions */
 int EXT_FID_MASK ; 
 int EXT_VID_MASK ; 
 int FID_MASK ; 
 int MAX_FREQ ; 
 int MIN_FREQ ; 
 int VID_MASK ; 
 int VID_OFF ; 
 int VID_SHIFT ; 
 int find_khz_freq_from_fid (int) ; 
 int /*<<< orphan*/  invalidate_entry (struct cpufreq_frequency_table*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_info (char*,int,unsigned int) ; 

__attribute__((used)) static int fill_powernow_table_fidvid(struct powernow_k8_data *data,
		struct cpufreq_frequency_table *powernow_table)
{
	int i;

	for (i = 0; i < data->acpi_data.state_count; i++) {
		u32 fid;
		u32 vid;
		u32 freq, index;
		u64 status, control;

		if (data->exttype) {
			status =  data->acpi_data.states[i].status;
			fid = status & EXT_FID_MASK;
			vid = (status >> VID_SHIFT) & EXT_VID_MASK;
		} else {
			control =  data->acpi_data.states[i].control;
			fid = control & FID_MASK;
			vid = (control >> VID_SHIFT) & VID_MASK;
		}

		pr_debug("   %d : fid 0x%x, vid 0x%x\n", i, fid, vid);

		index = fid | (vid<<8);
		powernow_table[i].driver_data = index;

		freq = find_khz_freq_from_fid(fid);
		powernow_table[i].frequency = freq;

		/* verify frequency is OK */
		if ((freq > (MAX_FREQ * 1000)) || (freq < (MIN_FREQ * 1000))) {
			pr_debug("invalid freq %u kHz, ignoring\n", freq);
			invalidate_entry(powernow_table, i);
			continue;
		}

		/* verify voltage is OK -
		 * BIOSs are using "off" to indicate invalid */
		if (vid == VID_OFF) {
			pr_debug("invalid vid %u, ignoring\n", vid);
			invalidate_entry(powernow_table, i);
			continue;
		}

		if (freq != (data->acpi_data.states[i].core_frequency * 1000)) {
			pr_info("invalid freq entries %u kHz vs. %u kHz\n",
				freq, (unsigned int)
				(data->acpi_data.states[i].core_frequency
				 * 1000));
			invalidate_entry(powernow_table, i);
			continue;
		}
	}
	return 0;
}