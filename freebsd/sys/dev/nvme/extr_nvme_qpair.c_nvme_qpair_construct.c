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
typedef  size_t uint64_t ;
typedef  void* uint32_t ;
struct nvme_tracker {int cid; size_t* prp; size_t prp_bus_addr; struct nvme_qpair* qpair; int /*<<< orphan*/  timer; int /*<<< orphan*/  payload_dma_map; } ;
struct nvme_qpair {int vector; int id; int num_entries; size_t num_trackers; int rid; size_t cmd_bus_addr; size_t cpl_bus_addr; int /*<<< orphan*/  domain; void* act_tr; int /*<<< orphan*/  free_tr; int /*<<< orphan*/  dma_tag_payload; int /*<<< orphan*/  queued_req; int /*<<< orphan*/  outstanding_tr; void* cq_hdbl_off; void* sq_tdbl_off; struct nvme_completion* cpl; struct nvme_command* cmd; scalar_t__ num_failures; scalar_t__ num_retries; scalar_t__ num_intr_handler_calls; scalar_t__ num_cmds; int /*<<< orphan*/  queuemem_map; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  lock; int /*<<< orphan*/  tag; int /*<<< orphan*/  res; struct nvme_controller* ctrlr; } ;
struct nvme_controller {int dstrd; int /*<<< orphan*/  dev; scalar_t__ msix_enabled; } ;
struct nvme_completion {int dummy; } ;
struct nvme_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  DOMAINSET_PREF (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NVME ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NVME_MAX_PRP_LIST_ENTRIES ; 
 int NVME_MAX_XFER_SIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct nvme_tracker*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_describe_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_set_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nvme_qpair*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * doorbell ; 
 void* malloc_domainset (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* nvme_mmio_offsetof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_printf (struct nvme_controller*,char*,...) ; 
 int /*<<< orphan*/  nvme_qpair_destroy (struct nvme_qpair*) ; 
 int /*<<< orphan*/  nvme_qpair_msix_handler ; 
 int /*<<< orphan*/  nvme_single_map ; 
 size_t roundup2 (uintptr_t,int) ; 
 int /*<<< orphan*/  tailq ; 
 scalar_t__ trunc_page (size_t) ; 

int
nvme_qpair_construct(struct nvme_qpair *qpair,
    uint32_t num_entries, uint32_t num_trackers,
    struct nvme_controller *ctrlr)
{
	struct nvme_tracker	*tr;
	size_t			cmdsz, cplsz, prpsz, allocsz, prpmemsz;
	uint64_t		queuemem_phys, prpmem_phys, list_phys;
	uint8_t			*queuemem, *prpmem, *prp_list;
	int			i, err;

	qpair->vector = ctrlr->msix_enabled ? qpair->id : 0;
	qpair->num_entries = num_entries;
	qpair->num_trackers = num_trackers;
	qpair->ctrlr = ctrlr;

	if (ctrlr->msix_enabled) {

		/*
		 * MSI-X vector resource IDs start at 1, so we add one to
		 *  the queue's vector to get the corresponding rid to use.
		 */
		qpair->rid = qpair->vector + 1;

		qpair->res = bus_alloc_resource_any(ctrlr->dev, SYS_RES_IRQ,
		    &qpair->rid, RF_ACTIVE);
		bus_setup_intr(ctrlr->dev, qpair->res,
		    INTR_TYPE_MISC | INTR_MPSAFE, NULL,
		    nvme_qpair_msix_handler, qpair, &qpair->tag);
		if (qpair->id == 0) {
			bus_describe_intr(ctrlr->dev, qpair->res, qpair->tag,
			    "admin");
		} else {
			bus_describe_intr(ctrlr->dev, qpair->res, qpair->tag,
			    "io%d", qpair->id - 1);
		}
	}

	mtx_init(&qpair->lock, "nvme qpair lock", NULL, MTX_DEF);

	/* Note: NVMe PRP format is restricted to 4-byte alignment. */
	err = bus_dma_tag_create(bus_get_dma_tag(ctrlr->dev),
	    4, PAGE_SIZE, BUS_SPACE_MAXADDR,
	    BUS_SPACE_MAXADDR, NULL, NULL, NVME_MAX_XFER_SIZE,
	    (NVME_MAX_XFER_SIZE/PAGE_SIZE)+1, PAGE_SIZE, 0,
	    NULL, NULL, &qpair->dma_tag_payload);
	if (err != 0) {
		nvme_printf(ctrlr, "payload tag create failed %d\n", err);
		goto out;
	}

	/*
	 * Each component must be page aligned, and individual PRP lists
	 * cannot cross a page boundary.
	 */
	cmdsz = qpair->num_entries * sizeof(struct nvme_command);
	cmdsz = roundup2(cmdsz, PAGE_SIZE);
	cplsz = qpair->num_entries * sizeof(struct nvme_completion);
	cplsz = roundup2(cplsz, PAGE_SIZE);
	prpsz = sizeof(uint64_t) * NVME_MAX_PRP_LIST_ENTRIES;;
	prpmemsz = qpair->num_trackers * prpsz;
	allocsz = cmdsz + cplsz + prpmemsz;

	err = bus_dma_tag_create(bus_get_dma_tag(ctrlr->dev),
	    PAGE_SIZE, 0, BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
	    allocsz, 1, allocsz, 0, NULL, NULL, &qpair->dma_tag);
	if (err != 0) {
		nvme_printf(ctrlr, "tag create failed %d\n", err);
		goto out;
	}
	bus_dma_tag_set_domain(qpair->dma_tag, qpair->domain);

	if (bus_dmamem_alloc(qpair->dma_tag, (void **)&queuemem,
	    BUS_DMA_NOWAIT, &qpair->queuemem_map)) {
		nvme_printf(ctrlr, "failed to alloc qpair memory\n");
		goto out;
	}

	if (bus_dmamap_load(qpair->dma_tag, qpair->queuemem_map,
	    queuemem, allocsz, nvme_single_map, &queuemem_phys, 0) != 0) {
		nvme_printf(ctrlr, "failed to load qpair memory\n");
		goto out;
	}

	qpair->num_cmds = 0;
	qpair->num_intr_handler_calls = 0;
	qpair->num_retries = 0;
	qpair->num_failures = 0;
	qpair->cmd = (struct nvme_command *)queuemem;
	qpair->cpl = (struct nvme_completion *)(queuemem + cmdsz);
	prpmem = (uint8_t *)(queuemem + cmdsz + cplsz);
	qpair->cmd_bus_addr = queuemem_phys;
	qpair->cpl_bus_addr = queuemem_phys + cmdsz;
	prpmem_phys = queuemem_phys + cmdsz + cplsz;

	/*
	 * Calcuate the stride of the doorbell register. Many emulators set this
	 * value to correspond to a cache line. However, some hardware has set
	 * it to various small values.
	 */
	qpair->sq_tdbl_off = nvme_mmio_offsetof(doorbell[0]) +
	    (qpair->id << (ctrlr->dstrd + 1));
	qpair->cq_hdbl_off = nvme_mmio_offsetof(doorbell[0]) +
	    (qpair->id << (ctrlr->dstrd + 1)) + (1 << ctrlr->dstrd);

	TAILQ_INIT(&qpair->free_tr);
	TAILQ_INIT(&qpair->outstanding_tr);
	STAILQ_INIT(&qpair->queued_req);

	list_phys = prpmem_phys;
	prp_list = prpmem;
	for (i = 0; i < qpair->num_trackers; i++) {

		if (list_phys + prpsz > prpmem_phys + prpmemsz) {
			qpair->num_trackers = i;
			break;
		}

		/*
		 * Make sure that the PRP list for this tracker doesn't
		 * overflow to another page.
		 */
		if (trunc_page(list_phys) !=
		    trunc_page(list_phys + prpsz - 1)) {
			list_phys = roundup2(list_phys, PAGE_SIZE);
			prp_list =
			    (uint8_t *)roundup2((uintptr_t)prp_list, PAGE_SIZE);
		}

		tr = malloc_domainset(sizeof(*tr), M_NVME,
		    DOMAINSET_PREF(qpair->domain), M_ZERO | M_WAITOK);
		bus_dmamap_create(qpair->dma_tag_payload, 0,
		    &tr->payload_dma_map);
		callout_init(&tr->timer, 1);
		tr->cid = i;
		tr->qpair = qpair;
		tr->prp = (uint64_t *)prp_list;
		tr->prp_bus_addr = list_phys;
		TAILQ_INSERT_HEAD(&qpair->free_tr, tr, tailq);
		list_phys += prpsz;
		prp_list += prpsz;
	}

	if (qpair->num_trackers == 0) {
		nvme_printf(ctrlr, "failed to allocate enough trackers\n");
		goto out;
	}

	qpair->act_tr = malloc_domainset(sizeof(struct nvme_tracker *) *
	    qpair->num_entries, M_NVME, DOMAINSET_PREF(qpair->domain),
	    M_ZERO | M_WAITOK);
	return (0);

out:
	nvme_qpair_destroy(qpair);
	return (ENOMEM);
}