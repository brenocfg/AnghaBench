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
typedef  scalar_t__ uint32_t ;
struct xhci_stream_ctx {int /*<<< orphan*/  qwSctx0; } ;
struct xhci_endp_ctx {int qwEpCtx2; int /*<<< orphan*/  dwEpCtx0; } ;
struct pci_xhci_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ XHCI_EPCTX_0_LSA_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ XHCI_EPCTX_0_MAXP_STREAMS_GET (int /*<<< orphan*/ ) ; 
 struct xhci_stream_ctx* XHCI_GADDR (struct pci_xhci_softc*,int) ; 
 int /*<<< orphan*/  XHCI_SCTX_0_SCT_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ XHCI_STREAMS_MAX ; 
 scalar_t__ XHCI_TRB_ERROR_INVALID_SID ; 
 scalar_t__ XHCI_TRB_ERROR_STREAM_TYPE ; 
 scalar_t__ XHCI_TRB_ERROR_SUCCESS ; 
 scalar_t__ XHCI_TRB_ERROR_TRB ; 

__attribute__((used)) static uint32_t
pci_xhci_find_stream(struct pci_xhci_softc *sc, struct xhci_endp_ctx *ep,
    uint32_t streamid, struct xhci_stream_ctx **osctx)
{
	struct xhci_stream_ctx *sctx;
	uint32_t	maxpstreams;

	maxpstreams = XHCI_EPCTX_0_MAXP_STREAMS_GET(ep->dwEpCtx0);
	if (maxpstreams == 0)
		return (XHCI_TRB_ERROR_TRB);

	if (maxpstreams > XHCI_STREAMS_MAX)
		return (XHCI_TRB_ERROR_INVALID_SID);

	if (XHCI_EPCTX_0_LSA_GET(ep->dwEpCtx0) == 0) {
		DPRINTF(("pci_xhci: find_stream; LSA bit not set\r\n"));
		return (XHCI_TRB_ERROR_INVALID_SID);
	}

	/* only support primary stream */
	if (streamid > maxpstreams)
		return (XHCI_TRB_ERROR_STREAM_TYPE);

	sctx = XHCI_GADDR(sc, ep->qwEpCtx2 & ~0xFUL) + streamid;
	if (!XHCI_SCTX_0_SCT_GET(sctx->qwSctx0))
		return (XHCI_TRB_ERROR_STREAM_TYPE);

	*osctx = sctx;

	return (XHCI_TRB_ERROR_SUCCESS);
}