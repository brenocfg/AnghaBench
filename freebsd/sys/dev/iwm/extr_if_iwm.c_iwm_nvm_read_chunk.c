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
typedef  int uint16_t ;
struct iwm_softc {int /*<<< orphan*/  sc_dev; } ;
struct iwm_rx_packet {scalar_t__ data; } ;
struct iwm_nvm_access_resp {int /*<<< orphan*/ * data; int /*<<< orphan*/  offset; int /*<<< orphan*/  length; int /*<<< orphan*/  status; } ;
struct iwm_nvm_access_cmd {int /*<<< orphan*/  op_code; int /*<<< orphan*/  type; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct iwm_host_cmd {int flags; int* len; struct iwm_rx_packet* resp_pkt; int /*<<< orphan*/  data; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int IWM_CMD_SEND_IN_RFKILL ; 
 int IWM_CMD_WANT_SKB ; 
 int IWM_DEBUG_EEPROM ; 
 int IWM_DEBUG_RESET ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int,char*,int) ; 
 int /*<<< orphan*/  IWM_NVM_ACCESS_CMD ; 
 int /*<<< orphan*/  IWM_NVM_READ_OPCODE ; 
 int IWM_READ_NVM_CHUNK_NOT_VALID_ADDRESS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  htole16 (int) ; 
 int /*<<< orphan*/  iwm_free_resp (struct iwm_softc*,struct iwm_host_cmd*) ; 
 int iwm_send_cmd (struct iwm_softc*,struct iwm_host_cmd*) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
iwm_nvm_read_chunk(struct iwm_softc *sc, uint16_t section,
	uint16_t offset, uint16_t length, uint8_t *data, uint16_t *len)
{
	struct iwm_nvm_access_cmd nvm_access_cmd = {
		.offset = htole16(offset),
		.length = htole16(length),
		.type = htole16(section),
		.op_code = IWM_NVM_READ_OPCODE,
	};
	struct iwm_nvm_access_resp *nvm_resp;
	struct iwm_rx_packet *pkt;
	struct iwm_host_cmd cmd = {
		.id = IWM_NVM_ACCESS_CMD,
		.flags = IWM_CMD_WANT_SKB | IWM_CMD_SEND_IN_RFKILL,
		.data = { &nvm_access_cmd, },
	};
	int ret, bytes_read, offset_read;
	uint8_t *resp_data;

	cmd.len[0] = sizeof(struct iwm_nvm_access_cmd);

	ret = iwm_send_cmd(sc, &cmd);
	if (ret) {
		device_printf(sc->sc_dev,
		    "Could not send NVM_ACCESS command (error=%d)\n", ret);
		return ret;
	}

	pkt = cmd.resp_pkt;

	/* Extract NVM response */
	nvm_resp = (void *)pkt->data;
	ret = le16toh(nvm_resp->status);
	bytes_read = le16toh(nvm_resp->length);
	offset_read = le16toh(nvm_resp->offset);
	resp_data = nvm_resp->data;
	if (ret) {
		if ((offset != 0) &&
		    (ret == IWM_READ_NVM_CHUNK_NOT_VALID_ADDRESS)) {
			/*
			 * meaning of NOT_VALID_ADDRESS:
			 * driver try to read chunk from address that is
			 * multiple of 2K and got an error since addr is empty.
			 * meaning of (offset != 0): driver already
			 * read valid data from another chunk so this case
			 * is not an error.
			 */
			IWM_DPRINTF(sc, IWM_DEBUG_EEPROM | IWM_DEBUG_RESET,
				    "NVM access command failed on offset 0x%x since that section size is multiple 2K\n",
				    offset);
			*len = 0;
			ret = 0;
		} else {
			IWM_DPRINTF(sc, IWM_DEBUG_EEPROM | IWM_DEBUG_RESET,
				    "NVM access command failed with status %d\n", ret);
			ret = EIO;
		}
		goto exit;
	}

	if (offset_read != offset) {
		device_printf(sc->sc_dev,
		    "NVM ACCESS response with invalid offset %d\n",
		    offset_read);
		ret = EINVAL;
		goto exit;
	}

	if (bytes_read > length) {
		device_printf(sc->sc_dev,
		    "NVM ACCESS response with too much data "
		    "(%d bytes requested, %d bytes received)\n",
		    length, bytes_read);
		ret = EINVAL;
		goto exit;
	}

	/* Write data to NVM */
	memcpy(data + offset, resp_data, bytes_read);
	*len = bytes_read;

 exit:
	iwm_free_resp(sc, &cmd);
	return ret;
}