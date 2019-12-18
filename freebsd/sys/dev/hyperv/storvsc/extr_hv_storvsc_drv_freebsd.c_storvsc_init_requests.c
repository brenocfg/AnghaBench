#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct storvsc_softc {int /*<<< orphan*/  storvsc_req_dtag; int /*<<< orphan*/  hs_free_list; TYPE_1__* hs_drv_props; } ;
struct hv_storvsc_request {int /*<<< orphan*/  data_dmap; struct storvsc_softc* softc; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int drv_max_ios_per_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 struct hv_storvsc_request* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct hv_storvsc_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct hv_storvsc_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  STORVSC_DATA_SEGCNT_MAX ; 
 int /*<<< orphan*/  STORVSC_DATA_SEGSZ_MAX ; 
 int /*<<< orphan*/  STORVSC_DATA_SIZE_MAX ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 struct storvsc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct hv_storvsc_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 struct hv_storvsc_request* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
storvsc_init_requests(device_t dev)
{
	struct storvsc_softc *sc = device_get_softc(dev);
	struct hv_storvsc_request *reqp;
	int error, i;

	LIST_INIT(&sc->hs_free_list);

	error = bus_dma_tag_create(
		bus_get_dma_tag(dev),		/* parent */
		1,				/* alignment */
		PAGE_SIZE,			/* boundary */
		BUS_SPACE_MAXADDR,		/* lowaddr */
		BUS_SPACE_MAXADDR,		/* highaddr */
		NULL, NULL,			/* filter, filterarg */
		STORVSC_DATA_SIZE_MAX,		/* maxsize */
		STORVSC_DATA_SEGCNT_MAX,	/* nsegments */
		STORVSC_DATA_SEGSZ_MAX,		/* maxsegsize */
		0,				/* flags */
		NULL,				/* lockfunc */
		NULL,				/* lockfuncarg */
		&sc->storvsc_req_dtag);
	if (error) {
		device_printf(dev, "failed to create storvsc dma tag\n");
		return (error);
	}

	for (i = 0; i < sc->hs_drv_props->drv_max_ios_per_target; ++i) {
		reqp = malloc(sizeof(struct hv_storvsc_request),
				 M_DEVBUF, M_WAITOK|M_ZERO);
		reqp->softc = sc;
		error = bus_dmamap_create(sc->storvsc_req_dtag, 0,
				&reqp->data_dmap);
		if (error) {
			device_printf(dev, "failed to allocate storvsc "
			    "data dmamap\n");
			goto cleanup;
		}
		LIST_INSERT_HEAD(&sc->hs_free_list, reqp, link);
	}
	return (0);

cleanup:
	while ((reqp = LIST_FIRST(&sc->hs_free_list)) != NULL) {
		LIST_REMOVE(reqp, link);
		bus_dmamap_destroy(sc->storvsc_req_dtag, reqp->data_dmap);
		free(reqp, M_DEVBUF);
	}
	return (error);
}