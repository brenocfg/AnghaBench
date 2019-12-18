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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct mem_ctl_info {struct amd64_pvt* pvt_info; } ;
struct mce {int status; int synd; int /*<<< orphan*/  addr; } ;
struct err_info {int syndrome; int csrow; int /*<<< orphan*/  err_code; int /*<<< orphan*/  channel; } ;
struct amd64_pvt {int /*<<< orphan*/  mc_node_id; } ;
typedef  int /*<<< orphan*/  err ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CHANNEL ; 
 int /*<<< orphan*/  ERR_NORM_ADDR ; 
 int /*<<< orphan*/  ERR_SYND ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int MCI_STATUS_DEFERRED ; 
 int MCI_STATUS_SYNDV ; 
 int /*<<< orphan*/  __log_ecc_error (struct mem_ctl_info*,struct err_info*,int) ; 
 struct mem_ctl_info* edac_mc_find (int) ; 
 int /*<<< orphan*/  error_address_to_page_and_offset (int /*<<< orphan*/ ,struct err_info*) ; 
 int /*<<< orphan*/  find_umc_channel (struct mce*) ; 
 int /*<<< orphan*/  memset (struct err_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ umc_normaddr_to_sysaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decode_umc_error(int node_id, struct mce *m)
{
	u8 ecc_type = (m->status >> 45) & 0x3;
	struct mem_ctl_info *mci;
	struct amd64_pvt *pvt;
	struct err_info err;
	u64 sys_addr;

	mci = edac_mc_find(node_id);
	if (!mci)
		return;

	pvt = mci->pvt_info;

	memset(&err, 0, sizeof(err));

	if (m->status & MCI_STATUS_DEFERRED)
		ecc_type = 3;

	err.channel = find_umc_channel(m);

	if (!(m->status & MCI_STATUS_SYNDV)) {
		err.err_code = ERR_SYND;
		goto log_error;
	}

	if (ecc_type == 2) {
		u8 length = (m->synd >> 18) & 0x3f;

		if (length)
			err.syndrome = (m->synd >> 32) & GENMASK(length - 1, 0);
		else
			err.err_code = ERR_CHANNEL;
	}

	err.csrow = m->synd & 0x7;

	if (umc_normaddr_to_sysaddr(m->addr, pvt->mc_node_id, err.channel, &sys_addr)) {
		err.err_code = ERR_NORM_ADDR;
		goto log_error;
	}

	error_address_to_page_and_offset(sys_addr, &err);

log_error:
	__log_ecc_error(mci, &err, ecc_type);
}