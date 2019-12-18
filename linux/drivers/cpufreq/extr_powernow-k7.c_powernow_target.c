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
struct TYPE_3__ {int CFID; } ;
union msr_fidvidstatus {TYPE_1__ bits; int /*<<< orphan*/  val; } ;
typedef  int u8 ;
struct cpufreq_policy {int dummy; } ;
struct cpufreq_freqs {int old; int new; } ;
struct TYPE_4__ {int driver_data; int frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_K7_FID_VID_STATUS ; 
 int /*<<< orphan*/  change_FID (int) ; 
 int /*<<< orphan*/  change_VID (int) ; 
 int* fid_codes ; 
 int fsb ; 
 int have_a0 ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 TYPE_2__* powernow_table ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int powernow_target(struct cpufreq_policy *policy, unsigned int index)
{
	u8 fid, vid;
	struct cpufreq_freqs freqs;
	union msr_fidvidstatus fidvidstatus;
	int cfid;

	/* fid are the lower 8 bits of the index we stored into
	 * the cpufreq frequency table in powernow_decode_bios,
	 * vid are the upper 8 bits.
	 */

	fid = powernow_table[index].driver_data & 0xFF;
	vid = (powernow_table[index].driver_data & 0xFF00) >> 8;

	rdmsrl(MSR_K7_FID_VID_STATUS, fidvidstatus.val);
	cfid = fidvidstatus.bits.CFID;
	freqs.old = fsb * fid_codes[cfid] / 10;

	freqs.new = powernow_table[index].frequency;

	/* Now do the magic poking into the MSRs.  */

	if (have_a0 == 1)	/* A0 errata 5 */
		local_irq_disable();

	if (freqs.old > freqs.new) {
		/* Going down, so change FID first */
		change_FID(fid);
		change_VID(vid);
	} else {
		/* Going up, so change VID first */
		change_VID(vid);
		change_FID(fid);
	}


	if (have_a0 == 1)
		local_irq_enable();

	return 0;
}