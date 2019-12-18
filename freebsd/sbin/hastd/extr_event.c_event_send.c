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
struct nv {int dummy; } ;
struct hast_resource {int /*<<< orphan*/  hr_event; } ;

/* Variables and functions */
 int EVENT_MAX ; 
 int EVENT_MIN ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int hast_proto_recv_hdr (int /*<<< orphan*/ ,struct nv**) ; 
 int hast_proto_send (struct hast_resource const*,int /*<<< orphan*/ ,struct nv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_add_uint8 (struct nv*,int /*<<< orphan*/ ,char*) ; 
 struct nv* nv_alloc () ; 
 int nv_error (struct nv*) ; 
 int /*<<< orphan*/  nv_free (struct nv*) ; 
 int /*<<< orphan*/  pjdlog_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*) ; 

void
event_send(const struct hast_resource *res, int event)
{
	struct nv *nvin, *nvout;
	int error;

	PJDLOG_ASSERT(res != NULL);
	PJDLOG_ASSERT(event >= EVENT_MIN && event <= EVENT_MAX);

	nvin = nvout = NULL;

	/*
	 * Prepare and send event to parent process.
	 */
	nvout = nv_alloc();
	nv_add_uint8(nvout, (uint8_t)event, "event");
	error = nv_error(nvout);
	if (error != 0) {
		pjdlog_common(LOG_ERR, 0, error,
		    "Unable to prepare event header");
		goto done;
	}
	if (hast_proto_send(res, res->hr_event, nvout, NULL, 0) == -1) {
		pjdlog_errno(LOG_ERR, "Unable to send event header");
		goto done;
	}
	if (hast_proto_recv_hdr(res->hr_event, &nvin) == -1) {
		pjdlog_errno(LOG_ERR, "Unable to receive event header");
		goto done;
	}
	/*
	 * Do nothing with the answer. We only wait for it to be sure not
	 * to exit too quickly after sending an event and exiting immediately.
	 */
done:
	if (nvin != NULL)
		nv_free(nvin);
	if (nvout != NULL)
		nv_free(nvout);
}