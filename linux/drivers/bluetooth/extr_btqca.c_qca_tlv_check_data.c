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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct tlv_type_patch {int download_mode; int format_version; int signature; int reserved1; int /*<<< orphan*/  entry; int /*<<< orphan*/  reserved2; int /*<<< orphan*/  patch_version; int /*<<< orphan*/  rom_build; int /*<<< orphan*/  product_id; int /*<<< orphan*/  data_length; int /*<<< orphan*/  total_size; } ;
struct tlv_type_nvm {int* data; int /*<<< orphan*/  tag_len; int /*<<< orphan*/  tag_id; } ;
struct tlv_type_hdr {int /*<<< orphan*/ * data; int /*<<< orphan*/  type_len; } ;
struct rome_config {int dnld_mode; int dnld_type; int type; int user_baud_rate; } ;
struct firmware {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int) ; 
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
#define  EDL_TAG_ID_DEEP_SLEEP 131 
#define  EDL_TAG_ID_HCI 130 
 void* ROME_SKIP_EVT_NONE ; 
#define  TLV_TYPE_NVM 129 
#define  TLV_TYPE_PATCH 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qca_tlv_check_data(struct rome_config *config,
				const struct firmware *fw)
{
	const u8 *data;
	u32 type_len;
	u16 tag_id, tag_len;
	int idx, length;
	struct tlv_type_hdr *tlv;
	struct tlv_type_patch *tlv_patch;
	struct tlv_type_nvm *tlv_nvm;

	tlv = (struct tlv_type_hdr *)fw->data;

	type_len = le32_to_cpu(tlv->type_len);
	length = (type_len >> 8) & 0x00ffffff;

	BT_DBG("TLV Type\t\t : 0x%x", type_len & 0x000000ff);
	BT_DBG("Length\t\t : %d bytes", length);

	config->dnld_mode = ROME_SKIP_EVT_NONE;
	config->dnld_type = ROME_SKIP_EVT_NONE;

	switch (config->type) {
	case TLV_TYPE_PATCH:
		tlv_patch = (struct tlv_type_patch *)tlv->data;

		/* For Rome version 1.1 to 3.1, all segment commands
		 * are acked by a vendor specific event (VSE).
		 * For Rome >= 3.2, the download mode field indicates
		 * if VSE is skipped by the controller.
		 * In case VSE is skipped, only the last segment is acked.
		 */
		config->dnld_mode = tlv_patch->download_mode;
		config->dnld_type = config->dnld_mode;

		BT_DBG("Total Length           : %d bytes",
		       le32_to_cpu(tlv_patch->total_size));
		BT_DBG("Patch Data Length      : %d bytes",
		       le32_to_cpu(tlv_patch->data_length));
		BT_DBG("Signing Format Version : 0x%x",
		       tlv_patch->format_version);
		BT_DBG("Signature Algorithm    : 0x%x",
		       tlv_patch->signature);
		BT_DBG("Download mode          : 0x%x",
		       tlv_patch->download_mode);
		BT_DBG("Reserved               : 0x%x",
		       tlv_patch->reserved1);
		BT_DBG("Product ID             : 0x%04x",
		       le16_to_cpu(tlv_patch->product_id));
		BT_DBG("Rom Build Version      : 0x%04x",
		       le16_to_cpu(tlv_patch->rom_build));
		BT_DBG("Patch Version          : 0x%04x",
		       le16_to_cpu(tlv_patch->patch_version));
		BT_DBG("Reserved               : 0x%x",
		       le16_to_cpu(tlv_patch->reserved2));
		BT_DBG("Patch Entry Address    : 0x%x",
		       le32_to_cpu(tlv_patch->entry));
		break;

	case TLV_TYPE_NVM:
		idx = 0;
		data = tlv->data;
		while (idx < length) {
			tlv_nvm = (struct tlv_type_nvm *)(data + idx);

			tag_id = le16_to_cpu(tlv_nvm->tag_id);
			tag_len = le16_to_cpu(tlv_nvm->tag_len);

			/* Update NVM tags as needed */
			switch (tag_id) {
			case EDL_TAG_ID_HCI:
				/* HCI transport layer parameters
				 * enabling software inband sleep
				 * onto controller side.
				 */
				tlv_nvm->data[0] |= 0x80;

				/* UART Baud Rate */
				tlv_nvm->data[2] = config->user_baud_rate;

				break;

			case EDL_TAG_ID_DEEP_SLEEP:
				/* Sleep enable mask
				 * enabling deep sleep feature on controller.
				 */
				tlv_nvm->data[0] |= 0x01;

				break;
			}

			idx += (sizeof(u16) + sizeof(u16) + 8 + tag_len);
		}
		break;

	default:
		BT_ERR("Unknown TLV type %d", config->type);
		break;
	}
}