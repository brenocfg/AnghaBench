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
struct qlnxr_iw_ep {int /*<<< orphan*/ * qp; int /*<<< orphan*/  ecore_context; struct qlnxr_dev* dev; } ;
struct qlnxr_dev {int /*<<< orphan*/  rdma_ctx; } ;
struct iw_cm_id {scalar_t__ provider_data; } ;
struct ecore_iwarp_reject_in {int /*<<< orphan*/  private_data_len; void const* private_data; struct qlnxr_iw_ep* cb_context; int /*<<< orphan*/  ep_context; } ;

/* Variables and functions */
 int EINVAL ; 
 int ecore_iwarp_reject (int /*<<< orphan*/ ,struct ecore_iwarp_reject_in*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
qlnxr_iw_reject(struct iw_cm_id *cm_id, const void *pdata, u8 pdata_len)
{
#if __FreeBSD_version >= 1102000

        struct qlnxr_iw_ep *ep = (struct qlnxr_iw_ep *)cm_id->provider_data;
        struct qlnxr_dev *dev = ep->dev;
        struct ecore_iwarp_reject_in params;
        int rc;

        params.ep_context = ep->ecore_context;
        params.cb_context = ep;
        params.private_data = pdata;
        params.private_data_len = pdata_len;
        ep->qp = NULL;

        rc = ecore_iwarp_reject(dev->rdma_ctx, &params);

        return rc;

#else

	printf("iWARP reject_cr not implemented\n");
	return -EINVAL;

#endif /* #if __FreeBSD_version >= 1102000 */
}