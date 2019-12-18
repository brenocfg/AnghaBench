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
struct TYPE_4__ {scalar_t__ kern_data_len; } ;
struct TYPE_3__ {int status; int flags; } ;
union ctl_io {TYPE_2__ scsiio; TYPE_1__ io_hdr; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct ctl_sg_entry {scalar_t__ len; scalar_t__ addr; } ;
struct ctl_ha_dt_req {unsigned int command; int ret; int /*<<< orphan*/  (* callback ) (struct ctl_ha_dt_req*) ;int /*<<< orphan*/ * remote; int /*<<< orphan*/ * local; scalar_t__ size; union ctl_io* context; } ;
typedef  int /*<<< orphan*/  (* ctl_ha_dt_cb ) (struct ctl_ha_dt_req*) ;

/* Variables and functions */
 int CTL_FLAG_BUS_ADDR ; 
 int CTL_HA_STATUS_SUCCESS ; 
 int CTL_HA_STATUS_WAIT ; 
 struct ctl_sg_entry* CTL_LSGL (union ctl_io*) ; 
 struct ctl_sg_entry* CTL_RSGL (union ctl_io*) ; 
 int CTL_STATUS_MASK ; 
 int CTL_STATUS_NONE ; 
 int CTL_SUCCESS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 struct ctl_ha_dt_req* ctl_dt_req_alloc () ; 
 int /*<<< orphan*/  ctl_dt_req_free (struct ctl_ha_dt_req*) ; 
 int ctl_dt_single (struct ctl_ha_dt_req*) ; 
 int /*<<< orphan*/  ctl_send_datamove_done (union ctl_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_busy (TYPE_2__*) ; 
 int /*<<< orphan*/ * vtophys (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctl_datamove_remote_xfer(union ctl_io *io, unsigned command,
			 ctl_ha_dt_cb callback)
{
	struct ctl_ha_dt_req *rq;
	struct ctl_sg_entry *remote_sglist, *local_sglist;
	uint32_t local_used, remote_used, total_used;
	int i, j, isc_ret;

	rq = ctl_dt_req_alloc();

	/*
	 * If we failed to allocate the request, and if the DMA didn't fail
	 * anyway, set busy status.  This is just a resource allocation
	 * failure.
	 */
	if ((rq == NULL)
	 && ((io->io_hdr.status & CTL_STATUS_MASK) != CTL_STATUS_NONE &&
	     (io->io_hdr.status & CTL_STATUS_MASK) != CTL_SUCCESS))
		ctl_set_busy(&io->scsiio);

	if ((io->io_hdr.status & CTL_STATUS_MASK) != CTL_STATUS_NONE &&
	    (io->io_hdr.status & CTL_STATUS_MASK) != CTL_SUCCESS) {

		if (rq != NULL)
			ctl_dt_req_free(rq);

		/*
		 * The data move failed.  We need to return status back
		 * to the other controller.  No point in trying to DMA
		 * data to the remote controller.
		 */

		ctl_send_datamove_done(io, /*have_lock*/ 0);

		return (1);
	}

	local_sglist = CTL_LSGL(io);
	remote_sglist = CTL_RSGL(io);
	local_used = 0;
	remote_used = 0;
	total_used = 0;

	/*
	 * Pull/push the data over the wire from/to the other controller.
	 * This takes into account the possibility that the local and
	 * remote sglists may not be identical in terms of the size of
	 * the elements and the number of elements.
	 *
	 * One fundamental assumption here is that the length allocated for
	 * both the local and remote sglists is identical.  Otherwise, we've
	 * essentially got a coding error of some sort.
	 */
	isc_ret = CTL_HA_STATUS_SUCCESS;
	for (i = 0, j = 0; total_used < io->scsiio.kern_data_len; ) {
		uint32_t cur_len;
		uint8_t *tmp_ptr;

		rq->command = command;
		rq->context = io;

		/*
		 * Both pointers should be aligned.  But it is possible
		 * that the allocation length is not.  They should both
		 * also have enough slack left over at the end, though,
		 * to round up to the next 8 byte boundary.
		 */
		cur_len = MIN(local_sglist[i].len - local_used,
			      remote_sglist[j].len - remote_used);
		rq->size = cur_len;

		tmp_ptr = (uint8_t *)local_sglist[i].addr;
		tmp_ptr += local_used;

#if 0
		/* Use physical addresses when talking to ISC hardware */
		if ((io->io_hdr.flags & CTL_FLAG_BUS_ADDR) == 0) {
			/* XXX KDM use busdma */
			rq->local = vtophys(tmp_ptr);
		} else
			rq->local = tmp_ptr;
#else
		KASSERT((io->io_hdr.flags & CTL_FLAG_BUS_ADDR) == 0,
		    ("HA does not support BUS_ADDR"));
		rq->local = tmp_ptr;
#endif

		tmp_ptr = (uint8_t *)remote_sglist[j].addr;
		tmp_ptr += remote_used;
		rq->remote = tmp_ptr;

		rq->callback = NULL;

		local_used += cur_len;
		if (local_used >= local_sglist[i].len) {
			i++;
			local_used = 0;
		}

		remote_used += cur_len;
		if (remote_used >= remote_sglist[j].len) {
			j++;
			remote_used = 0;
		}
		total_used += cur_len;

		if (total_used >= io->scsiio.kern_data_len)
			rq->callback = callback;

		isc_ret = ctl_dt_single(rq);
		if (isc_ret > CTL_HA_STATUS_SUCCESS)
			break;
	}
	if (isc_ret != CTL_HA_STATUS_WAIT) {
		rq->ret = isc_ret;
		callback(rq);
	}

	return (0);
}