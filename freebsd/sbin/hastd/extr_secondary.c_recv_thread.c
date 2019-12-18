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
struct nv {int dummy; } ;
struct hio {int hio_cmd; int hio_memsync; scalar_t__ hio_error; int /*<<< orphan*/  hio_data; } ;
struct hast_resource {int /*<<< orphan*/  hr_remotein; int /*<<< orphan*/  hr_stat_flush; int /*<<< orphan*/  hr_stat_delete; int /*<<< orphan*/  hr_stat_write; int /*<<< orphan*/  hr_stat_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_TEMPFAIL ; 
#define  HIO_DELETE 132 
#define  HIO_FLUSH 131 
#define  HIO_KEEPALIVE 130 
#define  HIO_READ 129 
#define  HIO_WRITE 128 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  MAXPHYS ; 
 int /*<<< orphan*/  PJDLOG_ABORT (char*,int) ; 
 int /*<<< orphan*/  QUEUE_INSERT (int /*<<< orphan*/ ,struct hio*) ; 
 int /*<<< orphan*/  QUEUE_TAKE (int /*<<< orphan*/ ,struct hio*) ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  free ; 
 int hast_proto_recv_data (struct hast_resource*,int /*<<< orphan*/ ,struct nv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hast_proto_recv_hdr (int /*<<< orphan*/ ,struct nv**) ; 
 int /*<<< orphan*/  hio_clear (struct hio*) ; 
 int /*<<< orphan*/  hio_copy (struct hio*,struct hio*) ; 
 int /*<<< orphan*/  nv_free (struct nv*) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*,...) ; 
 int /*<<< orphan*/  reqlog (int /*<<< orphan*/ ,int,int,struct hio*,char*,struct hio*) ; 
 scalar_t__ requnpack (struct hast_resource*,struct hio*,struct nv*) ; 
 int /*<<< orphan*/  secondary_exit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  send ; 

__attribute__((used)) static void *
recv_thread(void *arg)
{
	struct hast_resource *res = arg;
	struct hio *hio, *mshio;
	struct nv *nv;

	for (;;) {
		pjdlog_debug(2, "recv: Taking free request.");
		QUEUE_TAKE(free, hio);
		pjdlog_debug(2, "recv: (%p) Got request.", hio);
		if (hast_proto_recv_hdr(res->hr_remotein, &nv) == -1) {
			secondary_exit(EX_TEMPFAIL,
			    "Unable to receive request header");
		}
		if (requnpack(res, hio, nv) != 0) {
			nv_free(nv);
			pjdlog_debug(2,
			    "recv: (%p) Moving request to the send queue.",
			    hio);
			QUEUE_INSERT(send, hio);
			continue;
		}
		switch (hio->hio_cmd) {
		case HIO_READ:
			res->hr_stat_read++;
			break;
		case HIO_WRITE:
			res->hr_stat_write++;
			break;
		case HIO_DELETE:
			res->hr_stat_delete++;
			break;
		case HIO_FLUSH:
			res->hr_stat_flush++;
			break;
		case HIO_KEEPALIVE:
			break;
		default:
			PJDLOG_ABORT("Unexpected command (cmd=%hhu).",
			    hio->hio_cmd);
		}
		reqlog(LOG_DEBUG, 2, -1, hio,
		    "recv: (%p) Got request header: ", hio);
		if (hio->hio_cmd == HIO_KEEPALIVE) {
			nv_free(nv);
			pjdlog_debug(2,
			    "recv: (%p) Moving request to the free queue.",
			    hio);
			hio_clear(hio);
			QUEUE_INSERT(free, hio);
			continue;
		} else if (hio->hio_cmd == HIO_WRITE) {
			if (hast_proto_recv_data(res, res->hr_remotein, nv,
			    hio->hio_data, MAXPHYS) == -1) {
				secondary_exit(EX_TEMPFAIL,
				    "Unable to receive request data");
			}
			if (hio->hio_memsync) {
				/*
				 * For memsync requests we expect two replies.
				 * Clone the hio so we can handle both of them.
				 */
				pjdlog_debug(2, "recv: Taking free request.");
				QUEUE_TAKE(free, mshio);
				pjdlog_debug(2, "recv: (%p) Got request.",
				    mshio);
				hio_copy(hio, mshio);
				mshio->hio_error = 0;
				/*
				 * We want to keep 'memsync' tag only on the
				 * request going onto send queue (mshio).
				 */
				hio->hio_memsync = false;
				pjdlog_debug(2,
				    "recv: (%p) Moving memsync request to the send queue.",
				    mshio);
				QUEUE_INSERT(send, mshio);
			}
		}
		nv_free(nv);
		pjdlog_debug(2, "recv: (%p) Moving request to the disk queue.",
		    hio);
		QUEUE_INSERT(disk, hio);
	}
	/* NOTREACHED */
	return (NULL);
}