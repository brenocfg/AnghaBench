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
struct vmbus_xact {int dummy; } ;
struct rndis_halt_req {int rm_len; int /*<<< orphan*/  rm_rid; int /*<<< orphan*/  rm_type; } ;
struct hn_softc {int /*<<< orphan*/  hn_ifp; int /*<<< orphan*/  hn_xact; } ;
struct hn_nvs_sendctx {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  REMOTE_NDIS_HALT_MSG ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  hn_nvs_sendctx_init (struct hn_nvs_sendctx*,int /*<<< orphan*/ ,struct vmbus_xact*) ; 
 int /*<<< orphan*/  hn_nvs_sent_xact ; 
 int /*<<< orphan*/  hn_rndis_rid (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_rndis_xact_exec1 (struct hn_softc*,struct vmbus_xact*,int,struct hn_nvs_sendctx*,size_t*) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 
 struct vmbus_xact* vmbus_xact_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmbus_xact_put (struct vmbus_xact*) ; 
 struct rndis_halt_req* vmbus_xact_req_data (struct vmbus_xact*) ; 

__attribute__((used)) static int
hn_rndis_halt(struct hn_softc *sc)
{
	struct vmbus_xact *xact;
	struct rndis_halt_req *halt;
	struct hn_nvs_sendctx sndc;
	size_t comp_len;

	xact = vmbus_xact_get(sc->hn_xact, sizeof(*halt));
	if (xact == NULL) {
		if_printf(sc->hn_ifp, "no xact for RNDIS halt\n");
		return (ENXIO);
	}
	halt = vmbus_xact_req_data(xact);
	halt->rm_type = REMOTE_NDIS_HALT_MSG;
	halt->rm_len = sizeof(*halt);
	halt->rm_rid = hn_rndis_rid(sc);

	/* No RNDIS completion; rely on NVS message send completion */
	hn_nvs_sendctx_init(&sndc, hn_nvs_sent_xact, xact);
	hn_rndis_xact_exec1(sc, xact, sizeof(*halt), &sndc, &comp_len);

	vmbus_xact_put(xact);
	if (bootverbose)
		if_printf(sc->hn_ifp, "RNDIS halt done\n");
	return (0);
}