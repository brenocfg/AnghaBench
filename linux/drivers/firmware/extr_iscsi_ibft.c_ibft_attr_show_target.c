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
typedef  int u8 ;
struct TYPE_2__ {int index; int flags; } ;
struct ibft_tgt {int port; int nic_assoc; int chap_type; int /*<<< orphan*/  rev_chap_secret_off; int /*<<< orphan*/  rev_chap_secret_len; int /*<<< orphan*/  rev_chap_name_off; int /*<<< orphan*/  rev_chap_name_len; int /*<<< orphan*/  chap_secret_off; int /*<<< orphan*/  chap_secret_len; int /*<<< orphan*/  chap_name_off; int /*<<< orphan*/  chap_name_len; int /*<<< orphan*/  tgt_name_off; int /*<<< orphan*/  tgt_name_len; int /*<<< orphan*/ * lun; int /*<<< orphan*/  ip_addr; TYPE_1__ hdr; } ;
struct ibft_kobject {void* header; struct ibft_tgt* tgt; } ;
typedef  int ssize_t ;

/* Variables and functions */
#define  ISCSI_BOOT_TGT_CHAP_NAME 139 
#define  ISCSI_BOOT_TGT_CHAP_SECRET 138 
#define  ISCSI_BOOT_TGT_CHAP_TYPE 137 
#define  ISCSI_BOOT_TGT_FLAGS 136 
#define  ISCSI_BOOT_TGT_INDEX 135 
#define  ISCSI_BOOT_TGT_IP_ADDR 134 
#define  ISCSI_BOOT_TGT_LUN 133 
#define  ISCSI_BOOT_TGT_NAME 132 
#define  ISCSI_BOOT_TGT_NIC_ASSOC 131 
#define  ISCSI_BOOT_TGT_PORT 130 
#define  ISCSI_BOOT_TGT_REV_CHAP_NAME 129 
#define  ISCSI_BOOT_TGT_REV_CHAP_SECRET 128 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  sprintf_ipaddr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf_string (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t ibft_attr_show_target(void *data, int type, char *buf)
{
	struct ibft_kobject *entry = data;
	struct ibft_tgt *tgt = entry->tgt;
	void *ibft_loc = entry->header;
	char *str = buf;
	int i;

	if (!tgt)
		return 0;

	switch (type) {
	case ISCSI_BOOT_TGT_INDEX:
		str += sprintf(str, "%d\n", tgt->hdr.index);
		break;
	case ISCSI_BOOT_TGT_FLAGS:
		str += sprintf(str, "%d\n", tgt->hdr.flags);
		break;
	case ISCSI_BOOT_TGT_IP_ADDR:
		str += sprintf_ipaddr(str, tgt->ip_addr);
		break;
	case ISCSI_BOOT_TGT_PORT:
		str += sprintf(str, "%d\n", tgt->port);
		break;
	case ISCSI_BOOT_TGT_LUN:
		for (i = 0; i < 8; i++)
			str += sprintf(str, "%x", (u8)tgt->lun[i]);
		str += sprintf(str, "\n");
		break;
	case ISCSI_BOOT_TGT_NIC_ASSOC:
		str += sprintf(str, "%d\n", tgt->nic_assoc);
		break;
	case ISCSI_BOOT_TGT_CHAP_TYPE:
		str += sprintf(str, "%d\n", tgt->chap_type);
		break;
	case ISCSI_BOOT_TGT_NAME:
		str += sprintf_string(str, tgt->tgt_name_len,
				      (char *)ibft_loc + tgt->tgt_name_off);
		break;
	case ISCSI_BOOT_TGT_CHAP_NAME:
		str += sprintf_string(str, tgt->chap_name_len,
				      (char *)ibft_loc + tgt->chap_name_off);
		break;
	case ISCSI_BOOT_TGT_CHAP_SECRET:
		str += sprintf_string(str, tgt->chap_secret_len,
				      (char *)ibft_loc + tgt->chap_secret_off);
		break;
	case ISCSI_BOOT_TGT_REV_CHAP_NAME:
		str += sprintf_string(str, tgt->rev_chap_name_len,
				      (char *)ibft_loc +
				      tgt->rev_chap_name_off);
		break;
	case ISCSI_BOOT_TGT_REV_CHAP_SECRET:
		str += sprintf_string(str, tgt->rev_chap_secret_len,
				      (char *)ibft_loc +
				      tgt->rev_chap_secret_off);
		break;
	default:
		break;
	}

	return str - buf;
}