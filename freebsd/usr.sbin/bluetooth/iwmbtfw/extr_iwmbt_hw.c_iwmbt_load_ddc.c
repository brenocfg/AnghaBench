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
typedef  int /*<<< orphan*/  uint8_t ;
struct libusb_device_handle {int dummy; } ;
struct iwmbt_hci_cmd {scalar_t__ length; int /*<<< orphan*/  data; int /*<<< orphan*/  opcode; } ;
struct iwmbt_firmware {int len; scalar_t__* buf; int /*<<< orphan*/  fwname; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  IWMBT_HCI_CMD_TIMEOUT ; 
 int IWMBT_HCI_MAX_CMD_SIZE ; 
 int /*<<< orphan*/  XMIN (scalar_t__,int) ; 
 int /*<<< orphan*/  htole16 (int) ; 
 int /*<<< orphan*/  iwmbt_debug (char*,int,...) ; 
 int iwmbt_hci_command (struct libusb_device_handle*,struct iwmbt_hci_cmd*,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
iwmbt_load_ddc(struct libusb_device_handle *hdl,
    const struct iwmbt_firmware *ddc)
{
	int size, sent = 0;
	int ret, transferred;
	uint8_t buf[IWMBT_HCI_MAX_CMD_SIZE];
	struct iwmbt_hci_cmd *cmd = (struct iwmbt_hci_cmd *)buf;

	size = ddc->len;

	iwmbt_debug("file=%s, size=%d", ddc->fwname, size);

	while (size > 0) {

		memset(buf, 0, sizeof(buf));
		cmd->opcode = htole16(0xfc8b);
		cmd->length = ddc->buf[sent] + 1;
		memcpy(cmd->data, ddc->buf + sent, XMIN(ddc->buf[sent], size));

		iwmbt_debug("transferring %d bytes, offset %d",
		    cmd->length,
		    sent);

		size -= cmd->length;
		sent += cmd->length;

		ret = iwmbt_hci_command(hdl,
		    cmd,
		    buf,
		    sizeof(buf),
		    &transferred,
		    IWMBT_HCI_CMD_TIMEOUT);

		if (ret < 0) {
			 iwmbt_debug("Intel Write DDC failed: code=%d", ret);
			 return (-1);
		}
	}

	return (0);
}