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
struct powernow_k8_data {int currvid; int currfid; } ;

/* Variables and functions */
 int LO_FID_TABLE_TOP ; 
 int convert_fid_to_vco_fid (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 scalar_t__ query_current_values_with_pending_wait (struct powernow_k8_data*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ write_new_fid (struct powernow_k8_data*,int) ; 

__attribute__((used)) static int core_frequency_transition(struct powernow_k8_data *data, u32 reqfid)
{
	u32 vcoreqfid, vcocurrfid, vcofiddiff;
	u32 fid_interval, savevid = data->currvid;

	if (data->currfid == reqfid) {
		pr_err("ph2 null fid transition 0x%x\n", data->currfid);
		return 0;
	}

	pr_debug("ph2 (cpu%d): starting, currfid 0x%x, currvid 0x%x, reqfid 0x%x\n",
		smp_processor_id(),
		data->currfid, data->currvid, reqfid);

	vcoreqfid = convert_fid_to_vco_fid(reqfid);
	vcocurrfid = convert_fid_to_vco_fid(data->currfid);
	vcofiddiff = vcocurrfid > vcoreqfid ? vcocurrfid - vcoreqfid
	    : vcoreqfid - vcocurrfid;

	if ((reqfid <= LO_FID_TABLE_TOP) && (data->currfid <= LO_FID_TABLE_TOP))
		vcofiddiff = 0;

	while (vcofiddiff > 2) {
		(data->currfid & 1) ? (fid_interval = 1) : (fid_interval = 2);

		if (reqfid > data->currfid) {
			if (data->currfid > LO_FID_TABLE_TOP) {
				if (write_new_fid(data,
						data->currfid + fid_interval))
					return 1;
			} else {
				if (write_new_fid
				    (data,
				     2 + convert_fid_to_vco_fid(data->currfid)))
					return 1;
			}
		} else {
			if (write_new_fid(data, data->currfid - fid_interval))
				return 1;
		}

		vcocurrfid = convert_fid_to_vco_fid(data->currfid);
		vcofiddiff = vcocurrfid > vcoreqfid ? vcocurrfid - vcoreqfid
		    : vcoreqfid - vcocurrfid;
	}

	if (write_new_fid(data, reqfid))
		return 1;

	if (query_current_values_with_pending_wait(data))
		return 1;

	if (data->currfid != reqfid) {
		pr_err("ph2: mismatch, failed fid transition, curr 0x%x, req 0x%x\n",
			data->currfid, reqfid);
		return 1;
	}

	if (savevid != data->currvid) {
		pr_err("ph2: vid changed, save 0x%x, curr 0x%x\n",
			savevid, data->currvid);
		return 1;
	}

	pr_debug("ph2 complete, currfid 0x%x, currvid 0x%x\n",
		data->currfid, data->currvid);

	return 0;
}