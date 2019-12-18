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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iflib_dma_info {int /*<<< orphan*/  idi_paddr; int /*<<< orphan*/  idi_map; int /*<<< orphan*/  idi_tag; int /*<<< orphan*/  idi_vaddr; } ;
struct hwrm_nvm_modify_input {void* len; void* offset; int /*<<< orphan*/  dir_idx; int /*<<< orphan*/  host_src_addr; int /*<<< orphan*/  member_0; } ;
struct bnxt_softc {int /*<<< orphan*/  hwrm_cmd_timeo; int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_HWRM_LOCK (struct bnxt_softc*) ; 
 int /*<<< orphan*/  BNXT_HWRM_UNLOCK (struct bnxt_softc*) ; 
 int /*<<< orphan*/  BNXT_NVM_TIMEO ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HWRM_NVM_MODIFY ; 
 int _hwrm_send_message (struct bnxt_softc*,struct hwrm_nvm_modify_input*,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_nvm_modify_input*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int copyin (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 
 int iflib_dma_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iflib_dma_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_dma_free (struct iflib_dma_info*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

int
bnxt_hwrm_nvm_modify(struct bnxt_softc *softc, uint16_t index, uint32_t offset,
    void *data, bool cpyin, uint32_t length)
{
	struct hwrm_nvm_modify_input req = {0};
	struct iflib_dma_info dma_data;
	int rc;
	uint32_t old_timeo;

	if (length == 0 || !data)
		return EINVAL;
	rc = iflib_dma_alloc(softc->ctx, length, &dma_data,
	    BUS_DMA_NOWAIT);
	if (rc)
		return ENOMEM;
	if (cpyin) {
		rc = copyin(data, dma_data.idi_vaddr, length);
		if (rc)
			goto exit;
	}
	else
		memcpy(dma_data.idi_vaddr, data, length);
	bus_dmamap_sync(dma_data.idi_tag, dma_data.idi_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_NVM_MODIFY);
	req.host_src_addr = htole64(dma_data.idi_paddr);
	req.dir_idx = htole16(index);
	req.offset = htole32(offset);
	req.len = htole32(length);
	BNXT_HWRM_LOCK(softc);
	old_timeo = softc->hwrm_cmd_timeo;
	softc->hwrm_cmd_timeo = BNXT_NVM_TIMEO;
	rc = _hwrm_send_message(softc, &req, sizeof(req));
	softc->hwrm_cmd_timeo = old_timeo;
	BNXT_HWRM_UNLOCK(softc);

exit:
	iflib_dma_free(&dma_data);
	return rc;
}