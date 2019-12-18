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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iflib_dma_info {scalar_t__ idi_size; int /*<<< orphan*/  idi_map; int /*<<< orphan*/  idi_tag; int /*<<< orphan*/  idi_paddr; } ;
struct hwrm_nvm_read_input {void* len; void* offset; int /*<<< orphan*/  dir_idx; int /*<<< orphan*/  host_dest_addr; int /*<<< orphan*/  member_0; } ;
struct bnxt_softc {scalar_t__ hwrm_cmd_timeo; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_HWRM_LOCK (struct bnxt_softc*) ; 
 int /*<<< orphan*/  BNXT_HWRM_UNLOCK (struct bnxt_softc*) ; 
 scalar_t__ BNXT_NVM_TIMEO ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int EINVAL ; 
 int /*<<< orphan*/  HWRM_NVM_READ ; 
 int _hwrm_send_message (struct bnxt_softc*,struct hwrm_nvm_read_input*,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_nvm_read_input*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 void* htole32 (scalar_t__) ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 

int
bnxt_hwrm_nvm_read(struct bnxt_softc *softc, uint16_t index, uint32_t offset,
    uint32_t length, struct iflib_dma_info *data)
{
	struct hwrm_nvm_read_input req = {0};
	int rc;
	uint32_t old_timeo;

	if (length > data->idi_size) {
		rc = EINVAL;
		goto exit;
	}
	bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_NVM_READ);
	req.host_dest_addr = htole64(data->idi_paddr);
	req.dir_idx = htole16(index);
	req.offset = htole32(offset);
	req.len = htole32(length);
	BNXT_HWRM_LOCK(softc);
	old_timeo = softc->hwrm_cmd_timeo;
	softc->hwrm_cmd_timeo = BNXT_NVM_TIMEO;
	rc = _hwrm_send_message(softc, &req, sizeof(req));
	softc->hwrm_cmd_timeo = old_timeo;
	BNXT_HWRM_UNLOCK(softc);
	if (rc)
		goto exit;
	bus_dmamap_sync(data->idi_tag, data->idi_map, BUS_DMASYNC_POSTREAD);

	goto exit;

exit:
	return rc;
}