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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct nv {int dummy; } ;
struct hast_resource {int hr_extentsize; int /*<<< orphan*/  hr_ctrl; int /*<<< orphan*/  hr_role; int /*<<< orphan*/  (* output_status_aux ) (struct nv*) ;scalar_t__ hr_stat_activemap_flush_error; scalar_t__ hr_stat_flush_error; scalar_t__ hr_stat_delete_error; scalar_t__ hr_stat_activemap_write_error; scalar_t__ hr_stat_write_error; scalar_t__ hr_stat_read_error; scalar_t__ hr_stat_activemap_update; scalar_t__ hr_stat_flush; scalar_t__ hr_stat_delete; scalar_t__ hr_stat_write; scalar_t__ hr_stat_read; int /*<<< orphan*/  hr_amp; int /*<<< orphan*/  hr_keepdirty; int /*<<< orphan*/ * hr_remoteout; int /*<<< orphan*/ * hr_remotein; } ;

/* Variables and functions */
#define  CONTROL_RELOAD 129 
#define  CONTROL_STATUS 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  HAST_ROLE_PRIMARY ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  SIGTERM ; 
 int activemap_ndirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 int hast_proto_recv_hdr (int /*<<< orphan*/ ,struct nv**) ; 
 int hast_proto_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_add_int16 (struct nv*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nv_add_string (struct nv*,char*,char*) ; 
 int /*<<< orphan*/  nv_add_uint32 (struct nv*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nv_add_uint64 (struct nv*,scalar_t__,char*) ; 
 struct nv* nv_alloc () ; 
 scalar_t__ nv_error (struct nv*) ; 
 int /*<<< orphan*/  nv_free (struct nv*) ; 
 int /*<<< orphan*/  nv_get_uint8 (struct nv*,char*) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pjdlog_error (char*) ; 
 int /*<<< orphan*/  primary_config_reload (struct hast_resource*,struct nv*) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ sigexit_received ; 
 int /*<<< orphan*/  stub1 (struct nv*) ; 

void *
ctrl_thread(void *arg)
{
	struct hast_resource *res = arg;
	struct nv *nvin, *nvout;
	uint8_t cmd;

	for (;;) {
		if (hast_proto_recv_hdr(res->hr_ctrl, &nvin) == -1) {
			if (sigexit_received)
				pthread_exit(NULL);
			pjdlog_errno(LOG_ERR,
			    "Unable to receive control message");
			kill(getpid(), SIGTERM);
			pthread_exit(NULL);
		}
		cmd = nv_get_uint8(nvin, "cmd");
		if (cmd == 0) {
			pjdlog_error("Control message is missing 'cmd' field.");
			nv_free(nvin);
			continue;
		}
		nvout = nv_alloc();
		switch (cmd) {
		case CONTROL_STATUS:
			if (res->hr_remotein != NULL &&
			    res->hr_remoteout != NULL) {
				nv_add_string(nvout, "complete", "status");
			} else {
				nv_add_string(nvout, "degraded", "status");
			}
			nv_add_uint32(nvout, (uint32_t)res->hr_extentsize,
			    "extentsize");
			if (res->hr_role == HAST_ROLE_PRIMARY) {
				nv_add_uint32(nvout,
				    (uint32_t)res->hr_keepdirty, "keepdirty");
				nv_add_uint64(nvout,
				    (uint64_t)(activemap_ndirty(res->hr_amp) *
				    res->hr_extentsize), "dirty");
			} else {
				nv_add_uint32(nvout, (uint32_t)0, "keepdirty");
				nv_add_uint64(nvout, (uint64_t)0, "dirty");
			}
			nv_add_uint64(nvout, res->hr_stat_read, "stat_read");
			nv_add_uint64(nvout, res->hr_stat_write, "stat_write");
			nv_add_uint64(nvout, res->hr_stat_delete,
			    "stat_delete");
			nv_add_uint64(nvout, res->hr_stat_flush, "stat_flush");
			nv_add_uint64(nvout, res->hr_stat_activemap_update,
			    "stat_activemap_update");
			nv_add_uint64(nvout, res->hr_stat_read_error,
			    "stat_read_error");
			nv_add_uint64(nvout, res->hr_stat_write_error +
			    res->hr_stat_activemap_write_error,
			    "stat_write_error");
			nv_add_uint64(nvout, res->hr_stat_delete_error,
			    "stat_delete_error");
			nv_add_uint64(nvout, res->hr_stat_flush_error +
			    res->hr_stat_activemap_flush_error,
			    "stat_flush_error");
			res->output_status_aux(nvout);
			nv_add_int16(nvout, 0, "error");
			break;
		case CONTROL_RELOAD:
			/*
			 * When parent receives SIGHUP and discovers that
			 * something related to us has changes, it sends reload
			 * message to us.
			 */
			PJDLOG_ASSERT(res->hr_role == HAST_ROLE_PRIMARY);
			primary_config_reload(res, nvin);
			nv_add_int16(nvout, 0, "error");
			break;
		default:
			nv_add_int16(nvout, EINVAL, "error");
			break;
		}
		nv_free(nvin);
		if (nv_error(nvout) != 0) {
			pjdlog_error("Unable to create answer on control message.");
			nv_free(nvout);
			continue;
		}
		if (hast_proto_send(NULL, res->hr_ctrl, nvout, NULL, 0) == -1) {
			pjdlog_errno(LOG_ERR,
			    "Unable to send reply to control message");
		}
		nv_free(nvout);
	}
	/* NOTREACHED */
	return (NULL);
}