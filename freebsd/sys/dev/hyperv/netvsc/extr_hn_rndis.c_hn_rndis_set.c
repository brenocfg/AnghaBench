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
typedef  void* uint32_t ;
struct vmbus_xact {int dummy; } ;
struct rndis_set_req {size_t rm_len; size_t rm_infobuflen; int /*<<< orphan*/  rm_infobufoffset; void* rm_oid; void* rm_rid; int /*<<< orphan*/  rm_type; } ;
struct rndis_set_comp {scalar_t__ rm_status; } ;
struct hn_softc {int /*<<< orphan*/  hn_ifp; int /*<<< orphan*/  hn_xact; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  REMOTE_NDIS_SET_CMPLT ; 
 int /*<<< orphan*/  REMOTE_NDIS_SET_MSG ; 
 int /*<<< orphan*/  RNDIS_SET_REQ_INFOBUFOFFSET ; 
 scalar_t__ RNDIS_STATUS_SUCCESS ; 
 void* hn_rndis_rid (struct hn_softc*) ; 
 struct rndis_set_comp* hn_rndis_xact_execute (struct hn_softc*,struct vmbus_xact*,void*,size_t,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,void*,...) ; 
 int /*<<< orphan*/  memcpy (struct rndis_set_req*,void const*,size_t) ; 
 struct vmbus_xact* vmbus_xact_get (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  vmbus_xact_put (struct vmbus_xact*) ; 
 struct rndis_set_req* vmbus_xact_req_data (struct vmbus_xact*) ; 

__attribute__((used)) static int
hn_rndis_set(struct hn_softc *sc, uint32_t oid, const void *data, size_t dlen)
{
	struct rndis_set_req *req;
	const struct rndis_set_comp *comp;
	struct vmbus_xact *xact;
	size_t reqlen, comp_len;
	uint32_t rid;
	int error;

	KASSERT(dlen > 0, ("invalid dlen %zu", dlen));

	reqlen = sizeof(*req) + dlen;
	xact = vmbus_xact_get(sc->hn_xact, reqlen);
	if (xact == NULL) {
		if_printf(sc->hn_ifp, "no xact for RNDIS set 0x%08x\n", oid);
		return (ENXIO);
	}
	rid = hn_rndis_rid(sc);
	req = vmbus_xact_req_data(xact);
	req->rm_type = REMOTE_NDIS_SET_MSG;
	req->rm_len = reqlen;
	req->rm_rid = rid;
	req->rm_oid = oid;
	req->rm_infobuflen = dlen;
	req->rm_infobufoffset = RNDIS_SET_REQ_INFOBUFOFFSET;
	/* Data immediately follows RNDIS set. */
	memcpy(req + 1, data, dlen);

	comp_len = sizeof(*comp);
	comp = hn_rndis_xact_execute(sc, xact, rid, reqlen, &comp_len,
	    REMOTE_NDIS_SET_CMPLT);
	if (comp == NULL) {
		if_printf(sc->hn_ifp, "exec RNDIS set 0x%08x failed\n", oid);
		error = EIO;
		goto done;
	}

	if (comp->rm_status != RNDIS_STATUS_SUCCESS) {
		if_printf(sc->hn_ifp, "RNDIS set 0x%08x failed: "
		    "status 0x%08x\n", oid, comp->rm_status);
		error = EIO;
		goto done;
	}
	error = 0;
done:
	vmbus_xact_put(xact);
	return (error);
}