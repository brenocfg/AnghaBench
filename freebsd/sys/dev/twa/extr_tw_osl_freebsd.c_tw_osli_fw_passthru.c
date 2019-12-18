#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct twa_softc {int sg_size_factor; int /*<<< orphan*/  bus_dev; } ;
struct tw_cl_passthru_req_packet {int sgl_entries; int cmd_pkt_length; int /*<<< orphan*/ * cmd_pkt; } ;
struct TYPE_6__ {struct tw_cl_passthru_req_packet pt_req; } ;
struct tw_cl_req_packet {int status; TYPE_2__ gen_req_pkt; int /*<<< orphan*/  flags; int /*<<< orphan*/  tw_osl_callback; } ;
struct TYPE_5__ {struct tw_osli_req_context* osl_req_ctxt; } ;
struct tw_osli_req_context {int flags; int length; scalar_t__ state; int error_code; int /*<<< orphan*/ * data; TYPE_3__* ctlr; int /*<<< orphan*/  ioctl_wake_timeout_lock; struct tw_cl_req_packet req_pkt; int /*<<< orphan*/ * orig_req; TYPE_1__ req_handle; } ;
struct TYPE_8__ {int buffer_length; int os_status; } ;
struct tw_osli_ioctl_no_data_buf {TYPE_4__ driver_pkt; scalar_t__ pdata; int /*<<< orphan*/  cmd_pkt; } ;
struct tw_cl_command_packet {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ctlr_handle; } ;
typedef  int /*<<< orphan*/  TW_VOID ;
typedef  int TW_UINT32 ;
typedef  int TW_TIME ;
typedef  int /*<<< orphan*/  TW_INT8 ;
typedef  int TW_INT32 ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int TW_CL_ERR_REQ_BUS_RESET ; 
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER ; 
 int /*<<< orphan*/  TW_CL_REQ_RETRY_ON_BUSY ; 
 int /*<<< orphan*/  TW_CL_SEVERITY_ERROR_STRING ; 
 int /*<<< orphan*/  TW_OSLI_FREE_Q ; 
 int /*<<< orphan*/  TW_OSLI_MALLOC_CLASS ; 
 int TW_OSLI_REQ_FLAGS_DATA_IN ; 
 int TW_OSLI_REQ_FLAGS_DATA_OUT ; 
 int TW_OSLI_REQ_FLAGS_PASSTHRU ; 
 int TW_OSLI_REQ_FLAGS_SLEEPING ; 
 scalar_t__ TW_OSLI_REQ_STATE_COMPLETE ; 
 int copyin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int copyout (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ ) ; 
 int mtx_sleep (struct tw_osli_req_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_cl_is_reset_needed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tw_cl_reset_ctlr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tw_osl_complete_passthru ; 
 int tw_osl_get_local_time () ; 
 int /*<<< orphan*/  tw_osli_dbg_dprintf (int,struct twa_softc*,char*) ; 
 struct tw_osli_req_context* tw_osli_get_request (struct twa_softc*) ; 
 int tw_osli_map_request (struct tw_osli_req_context*) ; 
 int /*<<< orphan*/  tw_osli_printf (struct twa_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  tw_osli_req_q_insert_tail (struct tw_osli_req_context*,int /*<<< orphan*/ ) ; 

TW_INT32
tw_osli_fw_passthru(struct twa_softc *sc, TW_INT8 *buf)
{
	struct tw_osli_req_context		*req;
	struct tw_osli_ioctl_no_data_buf	*user_buf =
		(struct tw_osli_ioctl_no_data_buf *)buf;
	TW_TIME					end_time;
	TW_UINT32				timeout = 60;
	TW_UINT32				data_buf_size_adjusted;
	struct tw_cl_req_packet			*req_pkt;
	struct tw_cl_passthru_req_packet	*pt_req;
	TW_INT32				error;

	tw_osli_dbg_dprintf(5, sc, "ioctl: passthru");
		
	if ((req = tw_osli_get_request(sc)) == NULL)
		return(EBUSY);

	req->req_handle.osl_req_ctxt = req;
	req->orig_req = buf;
	req->flags |= TW_OSLI_REQ_FLAGS_PASSTHRU;

	req_pkt = &(req->req_pkt);
	req_pkt->status = 0;
	req_pkt->tw_osl_callback = tw_osl_complete_passthru;
	/* Let the Common Layer retry the request on cmd queue full. */
	req_pkt->flags |= TW_CL_REQ_RETRY_ON_BUSY;

	pt_req = &(req_pkt->gen_req_pkt.pt_req);
	/*
	 * Make sure that the data buffer sent to firmware is a 
	 * 512 byte multiple in size.
	 */
	data_buf_size_adjusted =
		(user_buf->driver_pkt.buffer_length +
		(sc->sg_size_factor - 1)) & ~(sc->sg_size_factor - 1);
	if ((req->length = data_buf_size_adjusted)) {
		if ((req->data = malloc(data_buf_size_adjusted,
			TW_OSLI_MALLOC_CLASS, M_WAITOK)) == NULL) {
			error = ENOMEM;
			tw_osli_printf(sc, "error = %d",
				TW_CL_SEVERITY_ERROR_STRING,
				TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
				0x2016,
				"Could not alloc mem for "
				"fw_passthru data_buf",
				error);
			goto fw_passthru_err;
		}
		/* Copy the payload. */
		if ((error = copyin((TW_VOID *)(user_buf->pdata), 
			req->data,
			user_buf->driver_pkt.buffer_length)) != 0) {
			tw_osli_printf(sc, "error = %d",
				TW_CL_SEVERITY_ERROR_STRING,
				TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
				0x2017,
				"Could not copyin fw_passthru data_buf",
				error);
			goto fw_passthru_err;
		}
		pt_req->sgl_entries = 1; /* will be updated during mapping */
		req->flags |= (TW_OSLI_REQ_FLAGS_DATA_IN |
			TW_OSLI_REQ_FLAGS_DATA_OUT);
	} else
		pt_req->sgl_entries = 0; /* no payload */

	pt_req->cmd_pkt = (TW_VOID *)(&(user_buf->cmd_pkt));
	pt_req->cmd_pkt_length = sizeof(struct tw_cl_command_packet);

	if ((error = tw_osli_map_request(req)))
		goto fw_passthru_err;

	end_time = tw_osl_get_local_time() + timeout;
	while (req->state != TW_OSLI_REQ_STATE_COMPLETE) {
		mtx_lock(req->ioctl_wake_timeout_lock);
		req->flags |= TW_OSLI_REQ_FLAGS_SLEEPING;

		error = mtx_sleep(req, req->ioctl_wake_timeout_lock, 0,
			    "twa_passthru", timeout*hz);
		mtx_unlock(req->ioctl_wake_timeout_lock);

		if (!(req->flags & TW_OSLI_REQ_FLAGS_SLEEPING))
			error = 0;
		req->flags &= ~TW_OSLI_REQ_FLAGS_SLEEPING;

		if (! error) {
			if (((error = req->error_code)) ||
				((error = (req->state !=
				TW_OSLI_REQ_STATE_COMPLETE))) ||
				((error = req_pkt->status)))
				goto fw_passthru_err;
			break;
		}

		if (req_pkt->status) {
			error = req_pkt->status;
			goto fw_passthru_err;
		}

		if (error == EWOULDBLOCK) {
			/* Time out! */
			if ((!(req->error_code))                       &&
			    (req->state == TW_OSLI_REQ_STATE_COMPLETE) &&
			    (!(req_pkt->status))			  ) {
#ifdef    TW_OSL_DEBUG
				tw_osli_printf(sc, "request = %p",
					TW_CL_SEVERITY_ERROR_STRING,
					TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
					0x7777,
					"FALSE Passthru timeout!",
					req);
#endif /* TW_OSL_DEBUG */
				error = 0; /* False error */
				break;
			}
			if (!(tw_cl_is_reset_needed(&(req->ctlr->ctlr_handle)))) {
#ifdef    TW_OSL_DEBUG
				tw_osli_printf(sc, "request = %p",
					TW_CL_SEVERITY_ERROR_STRING,
					TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
					0x2018,
					"Passthru request timed out!",
					req);
#else  /* TW_OSL_DEBUG */
			device_printf((sc)->bus_dev, "Passthru request timed out!\n");
#endif /* TW_OSL_DEBUG */
				tw_cl_reset_ctlr(&(req->ctlr->ctlr_handle));
			}

			error = 0;
			end_time = tw_osl_get_local_time() + timeout;
			continue;
			/*
			 * Don't touch req after a reset.  It (and any
			 * associated data) will be
			 * unmapped by the callback.
			 */
		}
		/* 
		 * Either the request got completed, or we were woken up by a
		 * signal.  Calculate the new timeout, in case it was the latter.
		 */
		timeout = (end_time - tw_osl_get_local_time());
	} /* End of while loop */

	/* If there was a payload, copy it back. */
	if ((!error) && (req->length))
		if ((error = copyout(req->data, user_buf->pdata,
			user_buf->driver_pkt.buffer_length)))
			tw_osli_printf(sc, "error = %d",
				TW_CL_SEVERITY_ERROR_STRING,
				TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
				0x2019,
				"Could not copyout fw_passthru data_buf",
				error);
	
fw_passthru_err:

	if (req_pkt->status == TW_CL_ERR_REQ_BUS_RESET)
		error = EBUSY;

	user_buf->driver_pkt.os_status = error;
	/* Free resources. */
	if (req->data)
		free(req->data, TW_OSLI_MALLOC_CLASS);
	tw_osli_req_q_insert_tail(req, TW_OSLI_FREE_Q);
	return(error);
}