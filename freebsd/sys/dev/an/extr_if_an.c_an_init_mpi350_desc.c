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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_2__ {scalar_t__ an_dma_paddr; } ;
struct an_softc {TYPE_1__ an_rid_buffer; int /*<<< orphan*/  an_ifp; TYPE_1__* an_tx_buffer; TYPE_1__* an_rx_buffer; } ;
struct an_reply {int an_valid; scalar_t__ an_phys; scalar_t__ an_rid; void* an_len; scalar_t__ an_eoc; scalar_t__ an_offset; scalar_t__ an_done; } ;
struct an_command {int an_parm2; void* an_parm1; int /*<<< orphan*/  an_parm0; void* an_cmd; } ;
struct an_card_tx_desc {int an_valid; scalar_t__ an_phys; scalar_t__ an_rid; void* an_len; scalar_t__ an_eoc; scalar_t__ an_offset; scalar_t__ an_done; } ;
struct an_card_rx_desc {int an_valid; scalar_t__ an_phys; scalar_t__ an_rid; void* an_len; scalar_t__ an_eoc; scalar_t__ an_offset; scalar_t__ an_done; } ;
struct an_card_rid_desc {int an_valid; scalar_t__ an_phys; scalar_t__ an_rid; void* an_len; scalar_t__ an_eoc; scalar_t__ an_offset; scalar_t__ an_done; } ;
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  an_tx_desc ;
typedef  int /*<<< orphan*/  an_rx_desc ;
typedef  int /*<<< orphan*/  an_rid_desc ;

/* Variables and functions */
 void* AN_CMD_ALLOC_DESC ; 
 int /*<<< orphan*/  AN_DESCRIPTOR_HOSTRW ; 
 int /*<<< orphan*/  AN_DESCRIPTOR_RX ; 
 int /*<<< orphan*/  AN_DESCRIPTOR_TX ; 
 void* AN_HOST_DESC_OFFSET ; 
 int /*<<< orphan*/  AN_LOCK_ASSERT (struct an_softc*) ; 
 int AN_MAX_RX_DESC ; 
 int AN_MAX_TX_DESC ; 
 void* AN_RID_BUFFER_SIZE ; 
 void* AN_RX_BUFFER_SIZE ; 
 void* AN_RX_DESC_OFFSET ; 
 void* AN_TX_BUFFER_SIZE ; 
 void* AN_TX_DESC_OFFSET ; 
 int /*<<< orphan*/  CSR_MEM_AUX_WRITE_4 (struct an_softc*,void*,int /*<<< orphan*/ ) ; 
 int EIO ; 
 scalar_t__ an_cmd_struct (struct an_softc*,struct an_command*,struct an_reply*) ; 
 int /*<<< orphan*/  an_dma_malloc (struct an_softc*,void*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct an_reply*,int) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 

int
an_init_mpi350_desc(struct an_softc *sc)
{
	struct an_command	cmd_struct;
	struct an_reply		reply;
	struct an_card_rid_desc an_rid_desc;
	struct an_card_rx_desc	an_rx_desc;
	struct an_card_tx_desc	an_tx_desc;
	int			i, desc;

	AN_LOCK_ASSERT(sc);
	if(!sc->an_rid_buffer.an_dma_paddr)
		an_dma_malloc(sc, AN_RID_BUFFER_SIZE,
				 &sc->an_rid_buffer, 0);
	for (i = 0; i < AN_MAX_RX_DESC; i++)
		if(!sc->an_rx_buffer[i].an_dma_paddr)
			an_dma_malloc(sc, AN_RX_BUFFER_SIZE,
				      &sc->an_rx_buffer[i], 0);
	for (i = 0; i < AN_MAX_TX_DESC; i++)
		if(!sc->an_tx_buffer[i].an_dma_paddr)
			an_dma_malloc(sc, AN_TX_BUFFER_SIZE,
				      &sc->an_tx_buffer[i], 0);

	/*
	 * Allocate RX descriptor
	 */
	bzero(&reply,sizeof(reply));
	cmd_struct.an_cmd   = AN_CMD_ALLOC_DESC;
	cmd_struct.an_parm0 = AN_DESCRIPTOR_RX;
	cmd_struct.an_parm1 = AN_RX_DESC_OFFSET;
	cmd_struct.an_parm2 = AN_MAX_RX_DESC;
	if (an_cmd_struct(sc, &cmd_struct, &reply)) {
		if_printf(sc->an_ifp, "failed to allocate RX descriptor\n");
		return(EIO);
	}

	for (desc = 0; desc < AN_MAX_RX_DESC; desc++) {
		bzero(&an_rx_desc, sizeof(an_rx_desc));
		an_rx_desc.an_valid = 1;
		an_rx_desc.an_len = AN_RX_BUFFER_SIZE;
		an_rx_desc.an_done = 0;
		an_rx_desc.an_phys = sc->an_rx_buffer[desc].an_dma_paddr;

		for (i = 0; i < sizeof(an_rx_desc) / 4; i++)
			CSR_MEM_AUX_WRITE_4(sc, AN_RX_DESC_OFFSET
			    + (desc * sizeof(an_rx_desc))
			    + (i * 4),
			    ((u_int32_t *)(void *)&an_rx_desc)[i]);
	}

	/*
	 * Allocate TX descriptor
	 */

	bzero(&reply,sizeof(reply));
	cmd_struct.an_cmd   = AN_CMD_ALLOC_DESC;
	cmd_struct.an_parm0 = AN_DESCRIPTOR_TX;
	cmd_struct.an_parm1 = AN_TX_DESC_OFFSET;
	cmd_struct.an_parm2 = AN_MAX_TX_DESC;
	if (an_cmd_struct(sc, &cmd_struct, &reply)) {
		if_printf(sc->an_ifp, "failed to allocate TX descriptor\n");
		return(EIO);
	}

	for (desc = 0; desc < AN_MAX_TX_DESC; desc++) {
		bzero(&an_tx_desc, sizeof(an_tx_desc));
		an_tx_desc.an_offset = 0;
		an_tx_desc.an_eoc = 0;
		an_tx_desc.an_valid = 0;
		an_tx_desc.an_len = 0;
		an_tx_desc.an_phys = sc->an_tx_buffer[desc].an_dma_paddr;

		for (i = 0; i < sizeof(an_tx_desc) / 4; i++)
			CSR_MEM_AUX_WRITE_4(sc, AN_TX_DESC_OFFSET
			    + (desc * sizeof(an_tx_desc))
			    + (i * 4),
			    ((u_int32_t *)(void *)&an_tx_desc)[i]);
	}

	/*
	 * Allocate RID descriptor
	 */

	bzero(&reply,sizeof(reply));
	cmd_struct.an_cmd   = AN_CMD_ALLOC_DESC;
	cmd_struct.an_parm0 = AN_DESCRIPTOR_HOSTRW;
	cmd_struct.an_parm1 = AN_HOST_DESC_OFFSET;
	cmd_struct.an_parm2 = 1;
	if (an_cmd_struct(sc, &cmd_struct, &reply)) {
		if_printf(sc->an_ifp, "failed to allocate host descriptor\n");
		return(EIO);
	}

	bzero(&an_rid_desc, sizeof(an_rid_desc));
	an_rid_desc.an_valid = 1;
	an_rid_desc.an_len = AN_RID_BUFFER_SIZE;
	an_rid_desc.an_rid = 0;
	an_rid_desc.an_phys = sc->an_rid_buffer.an_dma_paddr;

	for (i = 0; i < sizeof(an_rid_desc) / 4; i++)
		CSR_MEM_AUX_WRITE_4(sc, AN_HOST_DESC_OFFSET + i * 4,
				    ((u_int32_t *)(void *)&an_rid_desc)[i]);

	return(0);
}