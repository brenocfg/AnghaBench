#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct mwl_hal_vap {int macid; void* bss_type; void* vap_type; } ;
struct mwl_hal {int /*<<< orphan*/  mh_iot; int /*<<< orphan*/  mh_ioh; } ;
struct TYPE_6__ {int mh_devid; } ;
struct mwl_hal_priv {int mh_SDRAMSIZE_Addr; int /*<<< orphan*/  mh_mtx; int /*<<< orphan*/  mh_dmat; int /*<<< orphan*/  mh_dmamap; int /*<<< orphan*/  mh_cmdbuf; struct mwl_hal public; int /*<<< orphan*/  mh_cmdaddr; int /*<<< orphan*/  mh_mtxname; TYPE_3__ mh_revs; struct mwl_hal_vap* mh_vaps; TYPE_2__* mh_streams; int /*<<< orphan*/  mh_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
struct TYPE_4__ {size_t txq; } ;
struct TYPE_5__ {int stream; TYPE_1__ public; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  MTX_DEF ; 
 size_t MWL_BAQID_MAX ; 
 int MWL_BASTREAMS_MAX ; 
 int /*<<< orphan*/  MWL_CMDBUF_SIZE ; 
 void* MWL_HAL_AP ; 
 void* MWL_HAL_STA ; 
 int MWL_MBSS_AP_MAX ; 
 int MWL_MBSS_MAX ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  WL_MAC_TYPE_PRIMARY_AP ; 
 int /*<<< orphan*/  WL_MAC_TYPE_PRIMARY_CLIENT ; 
 int /*<<< orphan*/  WL_MAC_TYPE_SECONDARY_AP ; 
 int /*<<< orphan*/  WL_MAC_TYPE_SECONDARY_CLIENT ; 
 size_t* ba2qid ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  free (struct mwl_hal_priv*,int /*<<< orphan*/ ) ; 
 void* htole16 (int /*<<< orphan*/ ) ; 
 struct mwl_hal_priv* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl_hal_load_cb ; 
 int* qid2ba ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

struct mwl_hal *
mwl_hal_attach(device_t dev, uint16_t devid,
    bus_space_handle_t ioh, bus_space_tag_t iot, bus_dma_tag_t tag)
{
	struct mwl_hal_priv *mh;
	struct mwl_hal_vap *hvap;
	int error, i;

	mh = malloc(sizeof(struct mwl_hal_priv), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (mh == NULL)
		return NULL;
	mh->mh_dev = dev;
	mh->public.mh_ioh = ioh;
	mh->public.mh_iot = iot;
	for (i = 0; i < MWL_BASTREAMS_MAX; i++) {
		mh->mh_streams[i].public.txq = ba2qid[i];
		mh->mh_streams[i].stream = i;
		/* construct back-mapping while we're at it */
		if (mh->mh_streams[i].public.txq < MWL_BAQID_MAX)
			qid2ba[mh->mh_streams[i].public.txq] = i;
		else
			device_printf(dev, "unexpected BA tx qid %d for "
			    "stream %d\n", mh->mh_streams[i].public.txq, i);
	}
	/* setup constant portion of vap state */
	/* XXX should get max ap/client vap's from f/w */
	i = 0;
	hvap = &mh->mh_vaps[i];
	hvap->vap_type = MWL_HAL_AP;
	hvap->bss_type = htole16(WL_MAC_TYPE_PRIMARY_AP);
	hvap->macid = 0;
	for (i++; i < MWL_MBSS_AP_MAX; i++) {
		hvap = &mh->mh_vaps[i];
		hvap->vap_type = MWL_HAL_AP;
		hvap->bss_type = htole16(WL_MAC_TYPE_SECONDARY_AP);
		hvap->macid = i;
	}
	hvap = &mh->mh_vaps[i];
	hvap->vap_type = MWL_HAL_STA;
	hvap->bss_type = htole16(WL_MAC_TYPE_PRIMARY_CLIENT);
	hvap->macid = i;
	for (i++; i < MWL_MBSS_MAX; i++) {
		hvap = &mh->mh_vaps[i];
		hvap->vap_type = MWL_HAL_STA;
		hvap->bss_type = htole16(WL_MAC_TYPE_SECONDARY_CLIENT);
		hvap->macid = i;
	}
	mh->mh_revs.mh_devid = devid;
	snprintf(mh->mh_mtxname, sizeof(mh->mh_mtxname),
	    "%s_hal", device_get_nameunit(dev));
	mtx_init(&mh->mh_mtx, mh->mh_mtxname, NULL, MTX_DEF);

	/*
	 * Allocate the command buffer and map into the address
	 * space of the h/w.  We request "coherent" memory which
	 * will be uncached on some architectures.
	 */
	error = bus_dma_tag_create(tag,		/* parent */
		       PAGE_SIZE, 0,		/* alignment, bounds */
		       BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
		       BUS_SPACE_MAXADDR,	/* highaddr */
		       NULL, NULL,		/* filter, filterarg */
		       MWL_CMDBUF_SIZE,		/* maxsize */
		       1,			/* nsegments */
		       MWL_CMDBUF_SIZE,		/* maxsegsize */
		       BUS_DMA_ALLOCNOW,	/* flags */
		       NULL,			/* lockfunc */
		       NULL,			/* lockarg */
		       &mh->mh_dmat);
	if (error != 0) {
		device_printf(dev, "unable to allocate memory for cmd tag, "
			"error %u\n", error);
		goto fail0;
	}

	/* allocate descriptors */
	error = bus_dmamem_alloc(mh->mh_dmat, (void**) &mh->mh_cmdbuf,
				 BUS_DMA_NOWAIT | BUS_DMA_COHERENT, 
				 &mh->mh_dmamap);
	if (error != 0) {
		device_printf(dev, "unable to allocate memory for cmd buffer, "
			"error %u\n", error);
		goto fail1;
	}

	error = bus_dmamap_load(mh->mh_dmat, mh->mh_dmamap,
				mh->mh_cmdbuf, MWL_CMDBUF_SIZE,
				mwl_hal_load_cb, &mh->mh_cmdaddr,
				BUS_DMA_NOWAIT);
	if (error != 0) {
		device_printf(dev, "unable to load cmd buffer, error %u\n",
			error);
		goto fail2;
	}

	/*
	 * Some cards have SDRAM.  When loading firmware we need
	 * to reset the SDRAM controller prior to doing this.
	 * When the SDRAMSIZE is non-zero we do that work in
	 * mwl_hal_fwload.
	 */
	switch (devid) {
	case 0x2a02:		/* CB82 */
	case 0x2a03:		/* CB85 */
	case 0x2a08:		/* MC85_B1 */
	case 0x2a0b:		/* CB85AP */
	case 0x2a24:
		mh->mh_SDRAMSIZE_Addr = 0x40fe70b7;	/* 8M SDRAM */
		break;
	case 0x2a04:		/* MC85 */
		mh->mh_SDRAMSIZE_Addr = 0x40fc70b7;	/* 16M SDRAM */
		break;
	default:
		break;
	}
	return &mh->public;
fail2:
	bus_dmamem_free(mh->mh_dmat, mh->mh_cmdbuf, mh->mh_dmamap);
fail1:
	bus_dma_tag_destroy(mh->mh_dmat);
fail0:
	mtx_destroy(&mh->mh_mtx);
	free(mh, M_DEVBUF);
	return NULL;
}