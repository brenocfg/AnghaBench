#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union ucd_core_eid_ucode_block_num {unsigned long long value; int ucode_len; scalar_t__ ucode_blk; } ;
union aqm_grp_execmsk_lo {int exec_0_to_39; unsigned long long value; } ;
union aqm_grp_execmsk_hi {int exec_40_to_79; unsigned long long value; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct ucode {int /*<<< orphan*/  version; int /*<<< orphan*/ * code; int /*<<< orphan*/  code_size; } ;
struct TYPE_2__ {char** fw_name; int se_cores; int ae_cores; } ;
struct nitrox_device {TYPE_1__ hw; } ;
struct firmware {scalar_t__ data; } ;

/* Variables and functions */
 char* AE_FW ; 
 int /*<<< orphan*/  AQM_GRP_EXECMSK_HIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AQM_GRP_EXECMSK_LOX (int /*<<< orphan*/ ) ; 
 int CNN55XX_MAX_UCODE_SIZE ; 
 int CNN55XX_UCD_BLOCK_SIZE ; 
 int /*<<< orphan*/  DEFAULT_AE_GROUP ; 
 int /*<<< orphan*/  DEFAULT_SE_GROUP ; 
 int /*<<< orphan*/  DEV (struct nitrox_device*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  POM_GRP_EXECMASKX (int /*<<< orphan*/ ) ; 
 char* SE_FW ; 
 int /*<<< orphan*/  UCD_AE_EID_UCODE_BLOCK_NUMX (int) ; 
 int /*<<< orphan*/  UCD_SE_EID_UCODE_BLOCK_NUMX (int) ; 
 int VERSION_LEN ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_to_ucd_unit (struct nitrox_device*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int nitrox_load_fw(struct nitrox_device *ndev)
{
	const struct firmware *fw;
	const char *fw_name;
	struct ucode *ucode;
	u64 *ucode_data;
	u64 offset;
	union ucd_core_eid_ucode_block_num core_2_eid_val;
	union aqm_grp_execmsk_lo aqm_grp_execmask_lo;
	union aqm_grp_execmsk_hi aqm_grp_execmask_hi;
	u32 ucode_size;
	int ret, i = 0;

	fw_name = SE_FW;
	dev_info(DEV(ndev), "Loading firmware \"%s\"\n", fw_name);

	ret = request_firmware(&fw, fw_name, DEV(ndev));
	if (ret < 0) {
		dev_err(DEV(ndev), "failed to get firmware %s\n", fw_name);
		return ret;
	}

	ucode = (struct ucode *)fw->data;

	ucode_size = be32_to_cpu(ucode->code_size) * 2;
	if (!ucode_size || ucode_size > CNN55XX_MAX_UCODE_SIZE) {
		dev_err(DEV(ndev), "Invalid ucode size: %u for firmware %s\n",
			ucode_size, fw_name);
		release_firmware(fw);
		return -EINVAL;
	}
	ucode_data = ucode->code;

	/* copy the firmware version */
	memcpy(&ndev->hw.fw_name[0][0], ucode->version, (VERSION_LEN - 2));
	ndev->hw.fw_name[0][VERSION_LEN - 1] = '\0';

	/* Load SE Firmware on UCD Block 0 */
	write_to_ucd_unit(ndev, ucode_size, ucode_data, 0);

	release_firmware(fw);

	/* put all SE cores in DEFAULT_SE_GROUP */
	offset = POM_GRP_EXECMASKX(DEFAULT_SE_GROUP);
	nitrox_write_csr(ndev, offset, (~0ULL));

	/* write block number and firmware length
	 * bit:<2:0> block number
	 * bit:3 is set SE uses 32KB microcode
	 * bit:3 is clear SE uses 64KB microcode
	 */
	core_2_eid_val.value = 0ULL;
	core_2_eid_val.ucode_blk = 0;
	if (ucode_size <= CNN55XX_UCD_BLOCK_SIZE)
		core_2_eid_val.ucode_len = 1;
	else
		core_2_eid_val.ucode_len = 0;

	for (i = 0; i < ndev->hw.se_cores; i++) {
		offset = UCD_SE_EID_UCODE_BLOCK_NUMX(i);
		nitrox_write_csr(ndev, offset, core_2_eid_val.value);
	}


	fw_name = AE_FW;
	dev_info(DEV(ndev), "Loading firmware \"%s\"\n", fw_name);

	ret = request_firmware(&fw, fw_name, DEV(ndev));
	if (ret < 0) {
		dev_err(DEV(ndev), "failed to get firmware %s\n", fw_name);
		return ret;
	}

	ucode = (struct ucode *)fw->data;

	ucode_size = be32_to_cpu(ucode->code_size) * 2;
	if (!ucode_size || ucode_size > CNN55XX_MAX_UCODE_SIZE) {
		dev_err(DEV(ndev), "Invalid ucode size: %u for firmware %s\n",
			ucode_size, fw_name);
		release_firmware(fw);
		return -EINVAL;
	}
	ucode_data = ucode->code;

	/* copy the firmware version */
	memcpy(&ndev->hw.fw_name[1][0], ucode->version, (VERSION_LEN - 2));
	ndev->hw.fw_name[1][VERSION_LEN - 1] = '\0';

	/* Load AE Firmware on UCD Block 2 */
	write_to_ucd_unit(ndev, ucode_size, ucode_data, 2);

	release_firmware(fw);

	/* put all AE cores in DEFAULT_AE_GROUP */
	offset = AQM_GRP_EXECMSK_LOX(DEFAULT_AE_GROUP);
	aqm_grp_execmask_lo.exec_0_to_39 = 0xFFFFFFFFFFULL;
	nitrox_write_csr(ndev, offset, aqm_grp_execmask_lo.value);
	offset = AQM_GRP_EXECMSK_HIX(DEFAULT_AE_GROUP);
	aqm_grp_execmask_hi.exec_40_to_79 = 0xFFFFFFFFFFULL;
	nitrox_write_csr(ndev, offset, aqm_grp_execmask_hi.value);

	/* write block number and firmware length
	 * bit:<2:0> block number
	 * bit:3 is set SE uses 32KB microcode
	 * bit:3 is clear SE uses 64KB microcode
	 */
	core_2_eid_val.value = 0ULL;
	core_2_eid_val.ucode_blk = 0;
	if (ucode_size <= CNN55XX_UCD_BLOCK_SIZE)
		core_2_eid_val.ucode_len = 1;
	else
		core_2_eid_val.ucode_len = 0;

	for (i = 0; i < ndev->hw.ae_cores; i++) {
		offset = UCD_AE_EID_UCODE_BLOCK_NUMX(i);
		nitrox_write_csr(ndev, offset, core_2_eid_val.value);
	}

	return 0;
}