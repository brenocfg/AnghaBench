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
struct hio {int hio_cmd; scalar_t__ hio_error; size_t hio_length; void* hio_data; scalar_t__ hio_memsync; int /*<<< orphan*/  hio_seq; } ;
struct hast_resource {int /*<<< orphan*/  hr_remoteout; int /*<<< orphan*/  hr_stat_flush_error; int /*<<< orphan*/  hr_stat_delete_error; int /*<<< orphan*/  hr_stat_write_error; int /*<<< orphan*/  hr_stat_read_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_TEMPFAIL ; 
#define  HIO_DELETE 131 
#define  HIO_FLUSH 130 
#define  HIO_READ 129 
#define  HIO_WRITE 128 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  PJDLOG_ABORT (char*,int) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  QUEUE_INSERT (int /*<<< orphan*/ ,struct hio*) ; 
 int /*<<< orphan*/  QUEUE_TAKE (int /*<<< orphan*/ ,struct hio*) ; 
 int /*<<< orphan*/  free ; 
 int hast_proto_send (struct hast_resource*,int /*<<< orphan*/ ,struct nv*,void*,size_t) ; 
 int /*<<< orphan*/  hio_clear (struct hio*) ; 
 int /*<<< orphan*/  nv_add_int16 (struct nv*,scalar_t__,char*) ; 
 int /*<<< orphan*/  nv_add_int8 (struct nv*,int,char*) ; 
 int /*<<< orphan*/  nv_add_uint64 (struct nv*,int /*<<< orphan*/ ,char*) ; 
 struct nv* nv_alloc () ; 
 int /*<<< orphan*/  nv_free (struct nv*) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*,...) ; 
 int /*<<< orphan*/  reqlog (int /*<<< orphan*/ ,int,int,struct hio*,char*,struct hio*) ; 
 int /*<<< orphan*/  secondary_exit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  send ; 

__attribute__((used)) static void *
send_thread(void *arg)
{
	struct hast_resource *res = arg;
	struct nv *nvout;
	struct hio *hio;
	void *data;
	size_t length;

	for (;;) {
		pjdlog_debug(2, "send: Taking request.");
		QUEUE_TAKE(send, hio);
		reqlog(LOG_DEBUG, 2, -1, hio, "send: (%p) Got request: ", hio);
		nvout = nv_alloc();
		/* Copy sequence number. */
		nv_add_uint64(nvout, hio->hio_seq, "seq");
		if (hio->hio_memsync) {
			PJDLOG_ASSERT(hio->hio_cmd == HIO_WRITE);
			nv_add_int8(nvout, 1, "received");
		}
		switch (hio->hio_cmd) {
		case HIO_READ:
			if (hio->hio_error == 0) {
				data = hio->hio_data;
				length = hio->hio_length;
				break;
			}
			/*
			 * We send no data in case of an error.
			 */
			/* FALLTHROUGH */
		case HIO_DELETE:
		case HIO_FLUSH:
		case HIO_WRITE:
			data = NULL;
			length = 0;
			break;
		default:
			PJDLOG_ABORT("Unexpected command (cmd=%hhu).",
			    hio->hio_cmd);
		}
		if (hio->hio_error != 0) {
			switch (hio->hio_cmd) {
			case HIO_READ:
				res->hr_stat_read_error++;
				break;
			case HIO_WRITE:
				res->hr_stat_write_error++;
				break;
			case HIO_DELETE:
				res->hr_stat_delete_error++;
				break;
			case HIO_FLUSH:
				res->hr_stat_flush_error++;
				break;
			}
			nv_add_int16(nvout, hio->hio_error, "error");
		}
		if (hast_proto_send(res, res->hr_remoteout, nvout, data,
		    length) == -1) {
			secondary_exit(EX_TEMPFAIL, "Unable to send reply");
		}
		nv_free(nvout);
		pjdlog_debug(2, "send: (%p) Moving request to the free queue.",
		    hio);
		hio_clear(hio);
		QUEUE_INSERT(free, hio);
	}
	/* NOTREACHED */
	return (NULL);
}