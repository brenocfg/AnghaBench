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
typedef  int /*<<< orphan*/  u_int32_t ;
struct hpt_iop_request_ioctl_command {int /*<<< orphan*/  bytes_returned; int /*<<< orphan*/ * buf; } ;
struct hpt_iop_ioctl_param {scalar_t__ Magic; int nInBufferSize; int nOutBufferSize; scalar_t__ lpBytesReturned; scalar_t__ lpOutBuffer; scalar_t__ lpInBuffer; } ;
struct hpt_iop_hba {int config_done; scalar_t__ ctlcfg_ptr; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ HPT_IOCTL_MAGIC ; 
 scalar_t__ HPT_IOCTL_MAGIC32 ; 
 scalar_t__ copyin (void*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ copyout (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  hptiop_lock_adapter (struct hpt_iop_hba*) ; 
 scalar_t__ hptiop_post_ioctl_command_mvfrey (struct hpt_iop_hba*,struct hpt_iop_request_ioctl_command*,struct hpt_iop_ioctl_param*) ; 
 int /*<<< orphan*/  hptiop_unlock_adapter (struct hpt_iop_hba*) ; 

__attribute__((used)) static int hptiop_do_ioctl_mvfrey(struct hpt_iop_hba *hba,
				struct hpt_iop_ioctl_param *pParams)
{
	struct hpt_iop_request_ioctl_command *req;

	if ((pParams->Magic != HPT_IOCTL_MAGIC) &&
		(pParams->Magic != HPT_IOCTL_MAGIC32))
		return EFAULT;

	req = (struct hpt_iop_request_ioctl_command *)(hba->ctlcfg_ptr);
	hba->config_done = 0;
	hptiop_lock_adapter(hba);
	if (pParams->nInBufferSize)
		if (copyin((void *)pParams->lpInBuffer,
				req->buf, pParams->nInBufferSize))
			goto invalid;
	if (hptiop_post_ioctl_command_mvfrey(hba, req, pParams))
		goto invalid;

	if (hba->config_done == 1) {
		if (pParams->nOutBufferSize)
			if (copyout(req->buf +
				((pParams->nInBufferSize + 3) & ~3),
				(void *)pParams->lpOutBuffer,
				pParams->nOutBufferSize))
				goto invalid;

		if (pParams->lpBytesReturned)
			if (copyout(&req->bytes_returned,
				(void*)pParams->lpBytesReturned,
				sizeof(u_int32_t)))
				goto invalid;
		hptiop_unlock_adapter(hba);
		return 0;
	} else{
invalid:
		hptiop_unlock_adapter(hba);
		return EFAULT;
	}
}