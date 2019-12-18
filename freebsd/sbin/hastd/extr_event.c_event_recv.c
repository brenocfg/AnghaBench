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
typedef  int uint8_t ;
struct nv {int dummy; } ;
struct hast_resource {int /*<<< orphan*/  hr_event; int /*<<< orphan*/  hr_name; int /*<<< orphan*/  hr_exec; int /*<<< orphan*/  hr_role; } ;

/* Variables and functions */
#define  EVENT_CONNECT 133 
#define  EVENT_DISCONNECT 132 
 int EVENT_NONE ; 
#define  EVENT_SPLITBRAIN 131 
#define  EVENT_SYNCDONE 130 
#define  EVENT_SYNCINTR 129 
#define  EVENT_SYNCSTART 128 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int /*<<< orphan*/ ) ; 
 int errno ; 
 int hast_proto_recv_hdr (int /*<<< orphan*/ ,struct nv**) ; 
 int hast_proto_send (struct hast_resource const*,int /*<<< orphan*/ ,struct nv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hook_exec (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_add_int16 (struct nv*,int /*<<< orphan*/ ,char*) ; 
 struct nv* nv_alloc () ; 
 int nv_error (struct nv*) ; 
 int /*<<< orphan*/  nv_free (struct nv*) ; 
 int nv_get_uint8 (struct nv*,char*) ; 
 int /*<<< orphan*/  pjdlog_common (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pjdlog_error (char*,...) ; 
 int /*<<< orphan*/  pjdlog_prefix_set (char*,char*,...) ; 
 int /*<<< orphan*/  role2str (int /*<<< orphan*/ ) ; 

int
event_recv(const struct hast_resource *res)
{
	struct nv *nvin, *nvout;
	const char *evstr;
	uint8_t event;
	int error;

	PJDLOG_ASSERT(res != NULL);

	nvin = nvout = NULL;

	if (hast_proto_recv_hdr(res->hr_event, &nvin) == -1) {
		/*
		 * First error log as debug. This is because worker process
		 * most likely exited.
		 */
		pjdlog_common(LOG_DEBUG, 1, errno,
		    "Unable to receive event header");
		goto fail;
	}

	event = nv_get_uint8(nvin, "event");
	if (event == EVENT_NONE) {
		pjdlog_error("Event header is missing 'event' field.");
		goto fail;
	}

	switch (event) {
	case EVENT_CONNECT:
		evstr = "connect";
		break;
	case EVENT_DISCONNECT:
		evstr = "disconnect";
		break;
	case EVENT_SYNCSTART:
		evstr = "syncstart";
		break;
	case EVENT_SYNCDONE:
		evstr = "syncdone";
		break;
	case EVENT_SYNCINTR:
		evstr = "syncintr";
		break;
	case EVENT_SPLITBRAIN:
		evstr = "split-brain";
		break;
	default:
		pjdlog_error("Event header contain invalid event number (%hhu).",
		    event);
		goto fail;
	}

	pjdlog_prefix_set("[%s] (%s) ", res->hr_name, role2str(res->hr_role));
	hook_exec(res->hr_exec, evstr, res->hr_name, NULL);
	pjdlog_prefix_set("%s", "");

	nvout = nv_alloc();
	nv_add_int16(nvout, 0, "error");
	error = nv_error(nvout);
	if (error != 0) {
		pjdlog_common(LOG_ERR, 0, error,
		    "Unable to prepare event header");
		goto fail;
	}
	if (hast_proto_send(res, res->hr_event, nvout, NULL, 0) == -1) {
		pjdlog_errno(LOG_ERR, "Unable to send event header");
		goto fail;
	}
	nv_free(nvin);
	nv_free(nvout);
	return (0);
fail:
	if (nvin != NULL)
		nv_free(nvin);
	if (nvout != NULL)
		nv_free(nvout);
	return (-1);
}