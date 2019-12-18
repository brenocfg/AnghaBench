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
typedef  int uint32_t ;
struct vmbus_xact {int dummy; } ;
struct hn_softc {int /*<<< orphan*/  hn_ifp; int /*<<< orphan*/  hn_xact; } ;
struct hn_nvs_subch_resp {scalar_t__ nvs_status; int nvs_nsubch; } ;
struct hn_nvs_subch_req {int nvs_nsubch; int /*<<< orphan*/  nvs_op; int /*<<< orphan*/  nvs_type; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 scalar_t__ HN_NVS_STATUS_OK ; 
 int /*<<< orphan*/  HN_NVS_SUBCH_OP_ALLOC ; 
 int /*<<< orphan*/  HN_NVS_TYPE_SUBCH_REQ ; 
 int /*<<< orphan*/  HN_NVS_TYPE_SUBCH_RESP ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct hn_nvs_subch_resp* hn_nvs_xact_execute (struct hn_softc*,struct vmbus_xact*,struct hn_nvs_subch_req*,int,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct vmbus_xact* vmbus_xact_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmbus_xact_put (struct vmbus_xact*) ; 
 struct hn_nvs_subch_req* vmbus_xact_req_data (struct vmbus_xact*) ; 

int
hn_nvs_alloc_subchans(struct hn_softc *sc, int *nsubch0)
{
	struct vmbus_xact *xact;
	struct hn_nvs_subch_req *req;
	const struct hn_nvs_subch_resp *resp;
	int error, nsubch_req;
	uint32_t nsubch;
	size_t resp_len;

	nsubch_req = *nsubch0;
	KASSERT(nsubch_req > 0, ("invalid # of sub-channels %d", nsubch_req));

	xact = vmbus_xact_get(sc->hn_xact, sizeof(*req));
	if (xact == NULL) {
		if_printf(sc->hn_ifp, "no xact for nvs subch alloc\n");
		return (ENXIO);
	}
	req = vmbus_xact_req_data(xact);
	req->nvs_type = HN_NVS_TYPE_SUBCH_REQ;
	req->nvs_op = HN_NVS_SUBCH_OP_ALLOC;
	req->nvs_nsubch = nsubch_req;

	resp_len = sizeof(*resp);
	resp = hn_nvs_xact_execute(sc, xact, req, sizeof(*req), &resp_len,
	    HN_NVS_TYPE_SUBCH_RESP);
	if (resp == NULL) {
		if_printf(sc->hn_ifp, "exec nvs subch alloc failed\n");
		error = EIO;
		goto done;
	}
	if (resp->nvs_status != HN_NVS_STATUS_OK) {
		if_printf(sc->hn_ifp, "nvs subch alloc failed: %x\n",
		    resp->nvs_status);
		error = EIO;
		goto done;
	}

	nsubch = resp->nvs_nsubch;
	if (nsubch > nsubch_req) {
		if_printf(sc->hn_ifp, "%u subchans are allocated, "
		    "requested %d\n", nsubch, nsubch_req);
		nsubch = nsubch_req;
	}
	*nsubch0 = nsubch;
	error = 0;
done:
	vmbus_xact_put(xact);
	return (error);
}