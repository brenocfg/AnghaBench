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
struct iser_device {int /*<<< orphan*/  ib_device; } ;
struct TYPE_2__ {struct iser_device* device; } ;
struct iser_conn {int /*<<< orphan*/ * login_buf; int /*<<< orphan*/  login_resp_dma; int /*<<< orphan*/  login_req_dma; TYPE_1__ ib_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 int /*<<< orphan*/  ISER_RX_LOGIN_SIZE ; 
 int /*<<< orphan*/  M_ISER_INITIATOR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
iser_free_login_buf(struct iser_conn *iser_conn)
{
	struct iser_device *device = iser_conn->ib_conn.device;

	if (!iser_conn->login_buf)
		return;

	if (iser_conn->login_req_dma)
		ib_dma_unmap_single(device->ib_device,
				    iser_conn->login_req_dma,
				    ISCSI_DEF_MAX_RECV_SEG_LEN, DMA_TO_DEVICE);

	if (iser_conn->login_resp_dma)
		ib_dma_unmap_single(device->ib_device,
				    iser_conn->login_resp_dma,
				    ISER_RX_LOGIN_SIZE, DMA_FROM_DEVICE);

	free(iser_conn->login_buf, M_ISER_INITIATOR);

	/* make sure we never redo any unmapping */
	iser_conn->login_req_dma = 0;
	iser_conn->login_resp_dma = 0;
	iser_conn->login_buf = NULL;
}