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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct struct_vpd_data {int /*<<< orphan*/  fw_build; int /*<<< orphan*/  fw_micro; int /*<<< orphan*/  fw_minor; int /*<<< orphan*/  fw_major; int /*<<< orphan*/  vpd_vers; int /*<<< orphan*/  scfg_vers; int /*<<< orphan*/ * mn; int /*<<< orphan*/ * na; int /*<<< orphan*/ * bn; int /*<<< orphan*/ * sn; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {int size; scalar_t__ data; } ;
struct TYPE_2__ {int fw_vers; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  BN_MAX_LEN ; 
 int /*<<< orphan*/  BN_REG_ADDR ; 
 int /*<<< orphan*/  BN_T6_ADDR ; 
 int EDOOFUS ; 
 int /*<<< orphan*/  G_FW_HDR_FW_VER_BUILD (int) ; 
 int /*<<< orphan*/  G_FW_HDR_FW_VER_MAJOR (int) ; 
 int /*<<< orphan*/  G_FW_HDR_FW_VER_MICRO (int) ; 
 int /*<<< orphan*/  G_FW_HDR_FW_VER_MINOR (int) ; 
 int /*<<< orphan*/  MN_MAX_LEN ; 
 int /*<<< orphan*/  MN_REG_ADDR ; 
 int /*<<< orphan*/  MN_T6_ADDR ; 
 int /*<<< orphan*/  NA_MAX_LEN ; 
 int /*<<< orphan*/  NA_REG_ADDR ; 
 int /*<<< orphan*/  NA_T6_ADDR ; 
 int /*<<< orphan*/  SCFG_VER_ADDR ; 
 int /*<<< orphan*/  SCFG_VER_LEN ; 
 int /*<<< orphan*/  SN_MAX_LEN ; 
 int /*<<< orphan*/  SN_REG_ADDR ; 
 int /*<<< orphan*/  SN_T6_ADDR ; 
 int /*<<< orphan*/  VPD_VER_ADDR ; 
 int /*<<< orphan*/  VPD_VER_LEN ; 
 int compress_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int get_scratch_buff (struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 scalar_t__ is_fw_attached (struct cudbg_init*) ; 
 scalar_t__ is_t5 (struct adapter*) ; 
 scalar_t__ is_t6 (struct adapter*) ; 
 int read_vpd_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_scratch_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  simple_strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char,char) ; 
 int t4_get_fw_version (struct adapter*,int*) ; 
 int t4_get_scfg_version (struct adapter*,int /*<<< orphan*/ *) ; 
 int t4_get_vpd_version (struct adapter*,int /*<<< orphan*/ *) ; 
 int write_compression_hdr (struct cudbg_buffer*,struct cudbg_buffer*) ; 

__attribute__((used)) static int collect_vpd_data(struct cudbg_init *pdbg_init,
			    struct cudbg_buffer *dbg_buff,
			    struct cudbg_error *cudbg_err)
{
#ifdef notyet
	struct cudbg_buffer scratch_buff;
	struct adapter *padap = pdbg_init->adap;
	struct struct_vpd_data *vpd_data;
	char vpd_ver[4];
	u32 fw_vers;
	u32 size;
	int rc;

	size = sizeof(struct struct_vpd_data);
	scratch_buff.size = size;

	rc = get_scratch_buff(dbg_buff, scratch_buff.size, &scratch_buff);
	if (rc)
		goto err;

	vpd_data = (struct struct_vpd_data *)scratch_buff.data;

	if (is_t5(padap)) {
		read_vpd_reg(padap, SN_REG_ADDR, SN_MAX_LEN, vpd_data->sn);
		read_vpd_reg(padap, BN_REG_ADDR, BN_MAX_LEN, vpd_data->bn);
		read_vpd_reg(padap, NA_REG_ADDR, NA_MAX_LEN, vpd_data->na);
		read_vpd_reg(padap, MN_REG_ADDR, MN_MAX_LEN, vpd_data->mn);
	} else if (is_t6(padap)) {
		read_vpd_reg(padap, SN_T6_ADDR, SN_MAX_LEN, vpd_data->sn);
		read_vpd_reg(padap, BN_T6_ADDR, BN_MAX_LEN, vpd_data->bn);
		read_vpd_reg(padap, NA_T6_ADDR, NA_MAX_LEN, vpd_data->na);
		read_vpd_reg(padap, MN_T6_ADDR, MN_MAX_LEN, vpd_data->mn);
	}

	if (is_fw_attached(pdbg_init)) {
	   rc = t4_get_scfg_version(padap, &vpd_data->scfg_vers);
	} else {
		rc = 1;
	}

	if (rc) {
		/* Now trying with backdoor mechanism */
		rc = read_vpd_reg(padap, SCFG_VER_ADDR, SCFG_VER_LEN,
				  (u8 *)&vpd_data->scfg_vers);
		if (rc)
			goto err1;
	}

	if (is_fw_attached(pdbg_init)) {
		rc = t4_get_vpd_version(padap, &vpd_data->vpd_vers);
	} else {
		rc = 1;
	}

	if (rc) {
		/* Now trying with backdoor mechanism */
		rc = read_vpd_reg(padap, VPD_VER_ADDR, VPD_VER_LEN,
				  (u8 *)vpd_ver);
		if (rc)
			goto err1;
		/* read_vpd_reg return string of stored hex
		 * converting hex string to char string
		 * vpd version is 2 bytes only */
		sprintf(vpd_ver, "%c%c\n", vpd_ver[0], vpd_ver[1]);
		vpd_data->vpd_vers = simple_strtoul(vpd_ver, NULL, 16);
	}

	/* Get FW version if it's not already filled in */
	fw_vers = padap->params.fw_vers;
	if (!fw_vers) {
		rc = t4_get_fw_version(padap, &fw_vers);
		if (rc)
			goto err1;
	}

	vpd_data->fw_major = G_FW_HDR_FW_VER_MAJOR(fw_vers);
	vpd_data->fw_minor = G_FW_HDR_FW_VER_MINOR(fw_vers);
	vpd_data->fw_micro = G_FW_HDR_FW_VER_MICRO(fw_vers);
	vpd_data->fw_build = G_FW_HDR_FW_VER_BUILD(fw_vers);

	rc = write_compression_hdr(&scratch_buff, dbg_buff);
	if (rc)
		goto err1;

	rc = compress_buff(&scratch_buff, dbg_buff);

err1:
	release_scratch_buff(&scratch_buff, dbg_buff);
err:
	return rc;
#endif
	return (EDOOFUS);
}