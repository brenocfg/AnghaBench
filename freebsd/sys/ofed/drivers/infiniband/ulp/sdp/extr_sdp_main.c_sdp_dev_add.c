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
struct sdp_device {int /*<<< orphan*/  pd; int /*<<< orphan*/  fmr_pool; } ;
struct ib_fmr_pool_param {int access; int cache; int /*<<< orphan*/  dirty_watermark; int /*<<< orphan*/  pool_size; int /*<<< orphan*/  page_shift; int /*<<< orphan*/  max_pages_per_fmr; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_READ ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SDP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  SDP_FMR_DIRTY_SIZE ; 
 int /*<<< orphan*/  SDP_FMR_POOL_SIZE ; 
 int /*<<< orphan*/  SDP_FMR_SIZE ; 
 int /*<<< orphan*/  free (struct sdp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_alloc_pd (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_create_fmr_pool (int /*<<< orphan*/ ,struct ib_fmr_pool_param*) ; 
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct sdp_device*) ; 
 struct sdp_device* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ib_fmr_pool_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdp_client ; 

__attribute__((used)) static void
sdp_dev_add(struct ib_device *device)
{
	struct ib_fmr_pool_param param;
	struct sdp_device *sdp_dev;

	sdp_dev = malloc(sizeof(*sdp_dev), M_SDP, M_WAITOK | M_ZERO);
	sdp_dev->pd = ib_alloc_pd(device, 0);
	if (IS_ERR(sdp_dev->pd))
		goto out_pd;
	memset(&param, 0, sizeof param);
	param.max_pages_per_fmr = SDP_FMR_SIZE;
	param.page_shift = PAGE_SHIFT;
	param.access = (IB_ACCESS_LOCAL_WRITE | IB_ACCESS_REMOTE_READ);
	param.pool_size = SDP_FMR_POOL_SIZE;
	param.dirty_watermark = SDP_FMR_DIRTY_SIZE;
	param.cache = 1;
	sdp_dev->fmr_pool = ib_create_fmr_pool(sdp_dev->pd, &param);
	if (IS_ERR(sdp_dev->fmr_pool))
		goto out_fmr;
	ib_set_client_data(device, &sdp_client, sdp_dev);
	return;

out_fmr:
	ib_dealloc_pd(sdp_dev->pd);
out_pd:
	free(sdp_dev, M_SDP);
}