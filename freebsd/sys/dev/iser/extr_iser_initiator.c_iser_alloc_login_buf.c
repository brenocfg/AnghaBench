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
struct iser_conn {void* login_resp_dma; void* login_req_dma; scalar_t__ login_resp_buf; scalar_t__ login_req_buf; scalar_t__ login_buf; TYPE_1__ ib_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 scalar_t__ ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 int /*<<< orphan*/  ISER_DBG (char*) ; 
 scalar_t__ ISER_RX_LOGIN_SIZE ; 
 int /*<<< orphan*/  M_ISER_INITIATOR ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* ib_dma_map_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int ib_dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  iser_free_login_buf (struct iser_conn*) ; 
 scalar_t__ malloc (scalar_t__,int /*<<< orphan*/ ,int) ; 

int
iser_alloc_login_buf(struct iser_conn *iser_conn)
{
	struct iser_device *device = iser_conn->ib_conn.device;
	int req_err, resp_err;

	BUG_ON(device == NULL);

	iser_conn->login_buf = malloc(ISCSI_DEF_MAX_RECV_SEG_LEN + ISER_RX_LOGIN_SIZE,
				      M_ISER_INITIATOR, M_WAITOK | M_ZERO);

	if (!iser_conn->login_buf)
		goto out_err;

	iser_conn->login_req_buf  = iser_conn->login_buf;
	iser_conn->login_resp_buf = iser_conn->login_buf +
				    ISCSI_DEF_MAX_RECV_SEG_LEN;

	iser_conn->login_req_dma = ib_dma_map_single(device->ib_device,
						     iser_conn->login_req_buf,
						     ISCSI_DEF_MAX_RECV_SEG_LEN,
						     DMA_TO_DEVICE);

	iser_conn->login_resp_dma = ib_dma_map_single(device->ib_device,
						      iser_conn->login_resp_buf,
						      ISER_RX_LOGIN_SIZE,
						      DMA_FROM_DEVICE);

	req_err  = ib_dma_mapping_error(device->ib_device,
					iser_conn->login_req_dma);
	resp_err = ib_dma_mapping_error(device->ib_device,
					iser_conn->login_resp_dma);

	if (req_err || resp_err) {
		if (req_err)
			iser_conn->login_req_dma = 0;
		if (resp_err)
			iser_conn->login_resp_dma = 0;
		goto free_login_buf;
	}

	return (0);

free_login_buf:
	iser_free_login_buf(iser_conn);

out_err:
	ISER_DBG("unable to alloc or map login buf");
	return (ENOMEM);
}