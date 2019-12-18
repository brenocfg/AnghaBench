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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_int ;
struct scb_platform_data {int /*<<< orphan*/  io_timer; TYPE_1__* col_scb; struct hardware_scb* hscb; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  flags; struct ahd_softc* ahd_softc; void* sg_list_busaddr; void* sense_busaddr; int /*<<< orphan*/ * sense_data; int /*<<< orphan*/ * sg_list; struct scb_platform_data* sense_map; struct scb_platform_data* sg_map; struct scb_platform_data* hscb_map; struct scb_platform_data* platform_data; void* busaddr; int /*<<< orphan*/ * vaddr; } ;
struct scb_data {int numscbs; int scbs_left; int sgs_left; int sense_left; int /*<<< orphan*/  sense_dmat; int /*<<< orphan*/  sense_maps; int /*<<< orphan*/  sg_dmat; int /*<<< orphan*/  sg_maps; int /*<<< orphan*/  hscb_dmat; int /*<<< orphan*/  hscb_maps; } ;
struct scb {int /*<<< orphan*/  io_timer; TYPE_1__* col_scb; struct hardware_scb* hscb; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  flags; struct ahd_softc* ahd_softc; void* sg_list_busaddr; void* sense_busaddr; int /*<<< orphan*/ * sense_data; int /*<<< orphan*/ * sg_list; struct scb* sense_map; struct scb* sg_map; struct scb* hscb_map; struct scb* platform_data; void* busaddr; int /*<<< orphan*/ * vaddr; } ;
struct map_node {int /*<<< orphan*/  io_timer; TYPE_1__* col_scb; struct hardware_scb* hscb; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  flags; struct ahd_softc* ahd_softc; void* sg_list_busaddr; void* sense_busaddr; int /*<<< orphan*/ * sense_data; int /*<<< orphan*/ * sg_list; struct map_node* sense_map; struct map_node* sg_map; struct map_node* hscb_map; struct map_node* platform_data; void* busaddr; int /*<<< orphan*/ * vaddr; } ;
struct hardware_scb {int /*<<< orphan*/  tag; int /*<<< orphan*/  hscb_busaddr; } ;
struct ahd_softc {int flags; int /*<<< orphan*/  buffer_dmat; struct scb_data scb_data; } ;
struct ahd_dma_seg {int dummy; } ;
struct ahd_dma64_seg {int dummy; } ;
typedef  void* bus_addr_t ;
struct TYPE_2__ {struct scb_platform_data* col_scb; } ;

/* Variables and functions */
 int AHD_64BIT_ADDRESSING ; 
 int AHD_SCB_MAX_ALLOC ; 
 int AHD_SENSE_BUFSIZE ; 
 int AHD_SHOW_MEMORY ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_NOWAIT ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SCB_FLAG_NONE ; 
 struct scb_platform_data* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct scb_platform_data*,int /*<<< orphan*/ ) ; 
 int ahd_debug ; 
 int /*<<< orphan*/  ahd_dmamap_cb ; 
 TYPE_1__* ahd_find_scb_by_tag (struct ahd_softc*,int) ; 
 int /*<<< orphan*/  ahd_free_scb (struct ahd_softc*,struct scb_platform_data*) ; 
 int ahd_sglist_allocsize (struct ahd_softc*) ; 
 int ahd_sglist_size (struct ahd_softc*) ; 
 int aic_dmamap_create (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aic_dmamap_load (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ aic_dmamem_alloc (struct ahd_softc*,int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aic_htole16 (int) ; 
 int /*<<< orphan*/  aic_htole32 (void*) ; 
 int /*<<< orphan*/  aic_timer_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct scb_platform_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 struct scb_platform_data* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hardware_scb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
ahd_alloc_scbs(struct ahd_softc *ahd)
{
	struct scb_data *scb_data;
	struct scb	*next_scb;
	struct hardware_scb *hscb;
	struct map_node *hscb_map;
	struct map_node *sg_map;
	struct map_node *sense_map;
	uint8_t		*segs;
	uint8_t		*sense_data;
	bus_addr_t	 hscb_busaddr;
	bus_addr_t	 sg_busaddr;
	bus_addr_t	 sense_busaddr;
	int		 newcount;
	int		 i;

	scb_data = &ahd->scb_data;
	if (scb_data->numscbs >= AHD_SCB_MAX_ALLOC)
		/* Can't allocate any more */
		return (0);

	if (scb_data->scbs_left != 0) {
		int offset;

		offset = (PAGE_SIZE / sizeof(*hscb)) - scb_data->scbs_left;
		hscb_map = SLIST_FIRST(&scb_data->hscb_maps);
		hscb = &((struct hardware_scb *)hscb_map->vaddr)[offset];
		hscb_busaddr = hscb_map->busaddr + (offset * sizeof(*hscb));
	} else {
		hscb_map = malloc(sizeof(*hscb_map), M_DEVBUF, M_NOWAIT);

		if (hscb_map == NULL)
			return (0);

		/* Allocate the next batch of hardware SCBs */
		if (aic_dmamem_alloc(ahd, scb_data->hscb_dmat,
				     (void **)&hscb_map->vaddr,
				     BUS_DMA_NOWAIT | BUS_DMA_COHERENT,
				     &hscb_map->dmamap) != 0) {
			free(hscb_map, M_DEVBUF);
			return (0);
		}

		SLIST_INSERT_HEAD(&scb_data->hscb_maps, hscb_map, links);

		aic_dmamap_load(ahd, scb_data->hscb_dmat, hscb_map->dmamap,
				hscb_map->vaddr, PAGE_SIZE, ahd_dmamap_cb,
				&hscb_map->busaddr, /*flags*/0);

		hscb = (struct hardware_scb *)hscb_map->vaddr;
		hscb_busaddr = hscb_map->busaddr;
		scb_data->scbs_left = PAGE_SIZE / sizeof(*hscb);
	}

	if (scb_data->sgs_left != 0) {
		int offset;

		offset = ((ahd_sglist_allocsize(ahd) / ahd_sglist_size(ahd))
		       - scb_data->sgs_left) * ahd_sglist_size(ahd);
		sg_map = SLIST_FIRST(&scb_data->sg_maps);
		segs = sg_map->vaddr + offset;
		sg_busaddr = sg_map->busaddr + offset;
	} else {
		sg_map = malloc(sizeof(*sg_map), M_DEVBUF, M_NOWAIT);

		if (sg_map == NULL)
			return (0);

		/* Allocate the next batch of S/G lists */
		if (aic_dmamem_alloc(ahd, scb_data->sg_dmat,
				     (void **)&sg_map->vaddr,
				     BUS_DMA_NOWAIT | BUS_DMA_COHERENT,
				     &sg_map->dmamap) != 0) {
			free(sg_map, M_DEVBUF);
			return (0);
		}

		SLIST_INSERT_HEAD(&scb_data->sg_maps, sg_map, links);

		aic_dmamap_load(ahd, scb_data->sg_dmat, sg_map->dmamap,
				sg_map->vaddr, ahd_sglist_allocsize(ahd),
				ahd_dmamap_cb, &sg_map->busaddr, /*flags*/0);

		segs = sg_map->vaddr;
		sg_busaddr = sg_map->busaddr;
		scb_data->sgs_left =
		    ahd_sglist_allocsize(ahd) / ahd_sglist_size(ahd);
#ifdef AHD_DEBUG
		if (ahd_debug & AHD_SHOW_MEMORY)
			printf("Mapped SG data\n");
#endif
	}

	if (scb_data->sense_left != 0) {
		int offset;

		offset = PAGE_SIZE - (AHD_SENSE_BUFSIZE * scb_data->sense_left);
		sense_map = SLIST_FIRST(&scb_data->sense_maps);
		sense_data = sense_map->vaddr + offset;
		sense_busaddr = sense_map->busaddr + offset;
	} else {
		sense_map = malloc(sizeof(*sense_map), M_DEVBUF, M_NOWAIT);

		if (sense_map == NULL)
			return (0);

		/* Allocate the next batch of sense buffers */
		if (aic_dmamem_alloc(ahd, scb_data->sense_dmat,
				     (void **)&sense_map->vaddr,
				     BUS_DMA_NOWAIT, &sense_map->dmamap) != 0) {
			free(sense_map, M_DEVBUF);
			return (0);
		}

		SLIST_INSERT_HEAD(&scb_data->sense_maps, sense_map, links);

		aic_dmamap_load(ahd, scb_data->sense_dmat, sense_map->dmamap,
				sense_map->vaddr, PAGE_SIZE, ahd_dmamap_cb,
				&sense_map->busaddr, /*flags*/0);

		sense_data = sense_map->vaddr;
		sense_busaddr = sense_map->busaddr;
		scb_data->sense_left = PAGE_SIZE / AHD_SENSE_BUFSIZE;
#ifdef AHD_DEBUG
		if (ahd_debug & AHD_SHOW_MEMORY)
			printf("Mapped sense data\n");
#endif
	}

	newcount = MIN(scb_data->sense_left, scb_data->scbs_left);
	newcount = MIN(newcount, scb_data->sgs_left);
	newcount = MIN(newcount, (AHD_SCB_MAX_ALLOC - scb_data->numscbs));
	scb_data->sense_left -= newcount;
	scb_data->scbs_left -= newcount;
	scb_data->sgs_left -= newcount;
	for (i = 0; i < newcount; i++) {
		struct scb_platform_data *pdata;
		u_int col_tag;
#ifndef __linux__
		int error;
#endif

		next_scb = (struct scb *)malloc(sizeof(*next_scb),
						M_DEVBUF, M_NOWAIT);
		if (next_scb == NULL)
			break;

		pdata = (struct scb_platform_data *)malloc(sizeof(*pdata),
							   M_DEVBUF, M_NOWAIT);
		if (pdata == NULL) {
			free(next_scb, M_DEVBUF);
			break;
		}
		next_scb->platform_data = pdata;
		next_scb->hscb_map = hscb_map;
		next_scb->sg_map = sg_map;
		next_scb->sense_map = sense_map;
		next_scb->sg_list = segs;
		next_scb->sense_data = sense_data;
		next_scb->sense_busaddr = sense_busaddr;
		memset(hscb, 0, sizeof(*hscb));
		next_scb->hscb = hscb;
		hscb->hscb_busaddr = aic_htole32(hscb_busaddr);

		/*
		 * The sequencer always starts with the second entry.
		 * The first entry is embedded in the scb.
		 */
		next_scb->sg_list_busaddr = sg_busaddr;
		if ((ahd->flags & AHD_64BIT_ADDRESSING) != 0)
			next_scb->sg_list_busaddr
			    += sizeof(struct ahd_dma64_seg);
		else
			next_scb->sg_list_busaddr += sizeof(struct ahd_dma_seg);
		next_scb->ahd_softc = ahd;
		next_scb->flags = SCB_FLAG_NONE;
#ifndef __linux__
		error = aic_dmamap_create(ahd, ahd->buffer_dmat, /*flags*/0,
					  &next_scb->dmamap);
		if (error != 0) {
			free(next_scb, M_DEVBUF);
			free(pdata, M_DEVBUF);
			break;
		}
#endif
		next_scb->hscb->tag = aic_htole16(scb_data->numscbs);
		col_tag = scb_data->numscbs ^ 0x100;
		next_scb->col_scb = ahd_find_scb_by_tag(ahd, col_tag);
		if (next_scb->col_scb != NULL)
			next_scb->col_scb->col_scb = next_scb;
		aic_timer_init(&next_scb->io_timer);
		ahd_free_scb(ahd, next_scb);
		hscb++;
		hscb_busaddr += sizeof(*hscb);
		segs += ahd_sglist_size(ahd);
		sg_busaddr += ahd_sglist_size(ahd);
		sense_data += AHD_SENSE_BUFSIZE;
		sense_busaddr += AHD_SENSE_BUFSIZE;
		scb_data->numscbs++;
	}
	return (i);
}