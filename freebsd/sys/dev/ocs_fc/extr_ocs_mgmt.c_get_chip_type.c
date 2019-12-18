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
typedef  int /*<<< orphan*/  result_buf ;
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
typedef  int /*<<< orphan*/  ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_MODE_RD ; 
 int /*<<< orphan*/  SLI4_ASIC_ID_REG ; 
 int /*<<< orphan*/  SLI4_INTF_REG ; 
 int /*<<< orphan*/  SLI4_PCI_CLASS_REVISION ; 
 int ocs_config_read32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_mgmt_emit_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ocs_snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  ocs_strcmp (char*,char*) ; 
 int /*<<< orphan*/  ocs_strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static void
get_chip_type(ocs_t *ocs, char *name, ocs_textbuf_t *textbuf)
{
	uint32_t family;
	uint32_t asic_id;
	uint32_t asic_gen_num;
	uint32_t asic_rev_num;
	uint32_t rev_id;
	char result_buf[80];
	char tmp_buf[80];

	family = (ocs_config_read32(ocs, SLI4_INTF_REG) & 0x00000f00) >> 8;
	asic_id = ocs_config_read32(ocs, SLI4_ASIC_ID_REG);
	asic_rev_num = asic_id & 0xff;
	asic_gen_num = (asic_id & 0xff00) >> 8;

	rev_id = ocs_config_read32(ocs, SLI4_PCI_CLASS_REVISION) & 0xff;

	switch(family) {
	case 0x00:
		/* BE2 */
		ocs_strncpy(result_buf,  "BE2 A", sizeof(result_buf));
		ocs_snprintf(tmp_buf, 2, "%d", rev_id);
		strcat(result_buf, tmp_buf);
		break;
	case 0x01:
		/* BE3 */
		ocs_strncpy(result_buf, "BE3", sizeof(result_buf));
		if (rev_id >= 0x10) {
			strcat(result_buf, "-R");
		}
		ocs_snprintf(tmp_buf, 3, " %c", ((rev_id & 0xf0) >> 4) + 'A');
		strcat(result_buf, tmp_buf);
		ocs_snprintf(tmp_buf, 2, "%d", rev_id & 0x0f);
		strcat(result_buf, tmp_buf);
		break;
	case 0x02:
		/* Skyhawk A0 */
		ocs_strncpy(result_buf, "Skyhawk A0", sizeof(result_buf));
		break;
	case 0x0a:
		/* Lancer A0 */
		ocs_strncpy(result_buf, "Lancer A", sizeof(result_buf));
		ocs_snprintf(tmp_buf, 2, "%d", rev_id & 0x0f);
		strcat(result_buf, tmp_buf);
		break;
	case 0x0b:
		/* Lancer B0 or D0 */
		ocs_strncpy(result_buf, "Lancer", sizeof(result_buf));
		ocs_snprintf(tmp_buf, 3, " %c", ((rev_id & 0xf0) >> 4) + 'A');
		strcat(result_buf, tmp_buf);
		ocs_snprintf(tmp_buf, 2, "%d", rev_id & 0x0f);
		strcat(result_buf, tmp_buf);
		break;
	case 0x0c:
		ocs_strncpy(result_buf, "Lancer G6", sizeof(result_buf));
		break;
	case 0x0f:
		/* Refer to ASIC_ID */
		switch(asic_gen_num) {
		case 0x00:
			ocs_strncpy(result_buf, "BE2", sizeof(result_buf));
			break;
		case 0x03:
			ocs_strncpy(result_buf, "BE3-R", sizeof(result_buf));
			break;
		case 0x04:
			ocs_strncpy(result_buf, "Skyhawk-R", sizeof(result_buf));
			break;
		case 0x05:
			ocs_strncpy(result_buf, "Corsair", sizeof(result_buf));
			break;
		case 0x0b:
			ocs_strncpy(result_buf, "Lancer", sizeof(result_buf));
			break;
		case 0x0c:
			ocs_strncpy(result_buf, "LancerG6", sizeof(result_buf));
			break;
		default:
			ocs_strncpy(result_buf, "Unknown", sizeof(result_buf));
		}
		if (ocs_strcmp(result_buf, "Unknown") != 0) {
			ocs_snprintf(tmp_buf, 3, " %c", ((asic_rev_num & 0xf0) >> 4) + 'A');
			strcat(result_buf, tmp_buf);
			ocs_snprintf(tmp_buf, 2, "%d", asic_rev_num & 0x0f);
			strcat(result_buf, tmp_buf);
		}
		break;
	default:
		ocs_strncpy(result_buf, "Unknown", sizeof(result_buf));
	}

	ocs_mgmt_emit_string(textbuf, MGMT_MODE_RD, "chip_type", result_buf);

}