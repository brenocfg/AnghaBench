#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  nsid; int /*<<< orphan*/  cdw15; int /*<<< orphan*/  cdw14; int /*<<< orphan*/  cdw13; int /*<<< orphan*/  cdw12; int /*<<< orphan*/  cdw11; int /*<<< orphan*/  cdw10; int /*<<< orphan*/  rsvd3; int /*<<< orphan*/  rsvd2; int /*<<< orphan*/  fuse; int /*<<< orphan*/  opc; } ;
struct nvme_request {TYPE_2__ cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  cdw15; int /*<<< orphan*/  cdw14; int /*<<< orphan*/  cdw13; int /*<<< orphan*/  cdw12; int /*<<< orphan*/  cdw11; int /*<<< orphan*/  cdw10; int /*<<< orphan*/  rsvd3; int /*<<< orphan*/  rsvd2; int /*<<< orphan*/  fuse; int /*<<< orphan*/  opc; } ;
struct nvme_pt_command {scalar_t__ len; struct mtx* driver_lock; TYPE_1__ cmd; scalar_t__ buf; scalar_t__ is_read; } ;
struct nvme_controller {scalar_t__ max_xfer_size; } ;
struct mtx {int dummy; } ;
struct buf {scalar_t__ b_bufsize; scalar_t__ b_data; int /*<<< orphan*/  b_iocmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_READ ; 
 int /*<<< orphan*/  BIO_WRITE ; 
 int EFAULT ; 
 int EIO ; 
 scalar_t__ MAXPHYS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PHOLD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRELE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  curproc ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 struct mtx* mtx_pool_find (int /*<<< orphan*/ ,struct nvme_pt_command*) ; 
 int /*<<< orphan*/  mtx_sleep (struct nvme_pt_command*,struct mtx*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  mtxpool_sleep ; 
 struct nvme_request* nvme_allocate_request_null (int /*<<< orphan*/ ,struct nvme_pt_command*) ; 
 struct nvme_request* nvme_allocate_request_vaddr (scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct nvme_pt_command*) ; 
 int /*<<< orphan*/  nvme_ctrlr_submit_admin_request (struct nvme_controller*,struct nvme_request*) ; 
 int /*<<< orphan*/  nvme_ctrlr_submit_io_request (struct nvme_controller*,struct nvme_request*) ; 
 int /*<<< orphan*/  nvme_printf (struct nvme_controller*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nvme_pt_done ; 
 int /*<<< orphan*/  pbuf_zone ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 struct buf* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct buf*) ; 
 scalar_t__ vmapbuf (struct buf*,int) ; 

int
nvme_ctrlr_passthrough_cmd(struct nvme_controller *ctrlr,
    struct nvme_pt_command *pt, uint32_t nsid, int is_user_buffer,
    int is_admin_cmd)
{
	struct nvme_request	*req;
	struct mtx		*mtx;
	struct buf		*buf = NULL;
	int			ret = 0;
	vm_offset_t		addr, end;

	if (pt->len > 0) {
		/*
		 * vmapbuf calls vm_fault_quick_hold_pages which only maps full
		 * pages. Ensure this request has fewer than MAXPHYS bytes when
		 * extended to full pages.
		 */
		addr = (vm_offset_t)pt->buf;
		end = round_page(addr + pt->len);
		addr = trunc_page(addr);
		if (end - addr > MAXPHYS)
			return EIO;

		if (pt->len > ctrlr->max_xfer_size) {
			nvme_printf(ctrlr, "pt->len (%d) "
			    "exceeds max_xfer_size (%d)\n", pt->len,
			    ctrlr->max_xfer_size);
			return EIO;
		}
		if (is_user_buffer) {
			/*
			 * Ensure the user buffer is wired for the duration of
			 *  this pass-through command.
			 */
			PHOLD(curproc);
			buf = uma_zalloc(pbuf_zone, M_WAITOK);
			buf->b_data = pt->buf;
			buf->b_bufsize = pt->len;
			buf->b_iocmd = pt->is_read ? BIO_READ : BIO_WRITE;
			if (vmapbuf(buf, 1) < 0) {
				ret = EFAULT;
				goto err;
			}
			req = nvme_allocate_request_vaddr(buf->b_data, pt->len, 
			    nvme_pt_done, pt);
		} else
			req = nvme_allocate_request_vaddr(pt->buf, pt->len,
			    nvme_pt_done, pt);
	} else
		req = nvme_allocate_request_null(nvme_pt_done, pt);

	/* Assume user space already converted to little-endian */
	req->cmd.opc = pt->cmd.opc;
	req->cmd.fuse = pt->cmd.fuse;
	req->cmd.rsvd2 = pt->cmd.rsvd2;
	req->cmd.rsvd3 = pt->cmd.rsvd3;
	req->cmd.cdw10 = pt->cmd.cdw10;
	req->cmd.cdw11 = pt->cmd.cdw11;
	req->cmd.cdw12 = pt->cmd.cdw12;
	req->cmd.cdw13 = pt->cmd.cdw13;
	req->cmd.cdw14 = pt->cmd.cdw14;
	req->cmd.cdw15 = pt->cmd.cdw15;

	req->cmd.nsid = htole32(nsid);

	mtx = mtx_pool_find(mtxpool_sleep, pt);
	pt->driver_lock = mtx;

	if (is_admin_cmd)
		nvme_ctrlr_submit_admin_request(ctrlr, req);
	else
		nvme_ctrlr_submit_io_request(ctrlr, req);

	mtx_lock(mtx);
	while (pt->driver_lock != NULL)
		mtx_sleep(pt, mtx, PRIBIO, "nvme_pt", 0);
	mtx_unlock(mtx);

err:
	if (buf != NULL) {
		uma_zfree(pbuf_zone, buf);
		PRELE(curproc);
	}

	return (ret);
}