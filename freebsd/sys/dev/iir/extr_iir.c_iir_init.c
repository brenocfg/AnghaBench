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
typedef  int u_int16_t ;
struct gdt_softc {int* sc_gcscratch; int sc_info; int sc_bus_cnt; int* sc_bus_id; int sc_virt_bus; int sc_raw_feat; int sc_cache_feat; char* oem_name; scalar_t__ sc_vendor; int sc_info2; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_dpmembase; TYPE_2__* sc_hdr; int /*<<< orphan*/  sc_devnode; int /*<<< orphan*/  sc_status; int /*<<< orphan*/  sc_service; int /*<<< orphan*/  sc_fw_vers; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_init_level; int /*<<< orphan*/  sc_free_gccb; scalar_t__ sc_gcscratch_busbase; int /*<<< orphan*/  sc_buffer_dmat; struct gdt_ccb* sc_gccbs; int /*<<< orphan*/  sc_gcscratch_dmamap; int /*<<< orphan*/  sc_gcscratch_dmat; int /*<<< orphan*/  sc_parent_dmat; int /*<<< orphan*/  sc_ucmd_queue; int /*<<< orphan*/  sc_ccb_queue; int /*<<< orphan*/  sc_pending_gccb; int /*<<< orphan*/  sc_state; } ;
struct gdt_ccb {int gc_cmd_index; int* gc_scratch; int* gc_cmd; int /*<<< orphan*/  gc_timeout; scalar_t__ gc_scratch_busbase; int /*<<< orphan*/  gc_map_flag; int /*<<< orphan*/  gc_dmamap; int /*<<< orphan*/  gc_flags; } ;
typedef  int /*<<< orphan*/  gdt_statist_t ;
struct TYPE_4__ {int /*<<< orphan*/  scsi_host_drive_inquiry_vendor_id; } ;
struct TYPE_6__ {TYPE_1__ text; } ;
typedef  TYPE_3__ gdt_oem_str_record_t ;
typedef  int /*<<< orphan*/  gdt_oem_record_t ;
struct TYPE_5__ {int hd_present; int hd_size; int hd_heads; int hd_secs; int hd_devtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int DFLTPHYS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GDT_CACHESERVICE ; 
 int GDT_CMD_SZ ; 
 int /*<<< orphan*/  GDT_DEVTYPE ; 
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_DEBUG ; 
 int /*<<< orphan*/  GDT_D_INIT ; 
 int /*<<< orphan*/  GDT_GCF_UNUSED ; 
 int GDT_GETCH_CHANNEL_NO ; 
 size_t GDT_GETCH_SIOP_ID ; 
 int GDT_GETCH_SZ ; 
 int /*<<< orphan*/  GDT_GET_FEAT ; 
 int /*<<< orphan*/  GDT_INFO ; 
 int /*<<< orphan*/  GDT_INIT ; 
 int GDT_INVALID_CHANNEL ; 
 int GDT_IOCHAN_RAW_DESC ; 
 int /*<<< orphan*/  GDT_IOCTL ; 
 size_t GDT_IOC_CHAN_COUNT ; 
 size_t GDT_IOC_FIRST_CHAN ; 
 int GDT_IOC_HDR_SZ ; 
 size_t GDT_IOC_LAST_CHAN ; 
 size_t GDT_IOC_LIST_ENTRIES ; 
 int GDT_IOC_LIST_OFFSET ; 
 int GDT_IOC_NEWEST ; 
 int GDT_IOC_VERSION ; 
 int GDT_IO_CHANNEL ; 
 int GDT_LINUX_OS ; 
 int GDT_L_CTRL_PATTERN ; 
 int GDT_MAXBUS ; 
 int GDT_MAXCMDS ; 
 int GDT_MAXID_FC ; 
 int GDT_MAXSG ; 
 int GDT_MAX_HDRIVES ; 
 int GDT_OEM_BUFSIZE ; 
 int GDT_OEM_STR_RECORD ; 
 int GDT_OEM_VERSION ; 
 int /*<<< orphan*/  GDT_POLLING ; 
 int GDT_RAWIOC_PROC_ID ; 
 int GDT_RAWIOC_SZ ; 
 int GDT_SCATTER_GATHER ; 
 int GDT_SCRATCH_SZ ; 
 int /*<<< orphan*/  GDT_SCREENSERVICE ; 
 int /*<<< orphan*/  GDT_SCSIRAWSERVICE ; 
 int GDT_SCSI_CHAN_CNT ; 
 int GDT_SECS32 ; 
 int /*<<< orphan*/  GDT_SET_FEAT ; 
 int /*<<< orphan*/  GDT_UNFREEZE_IO ; 
 scalar_t__ INTEL_VENDOR_ID_IIR ; 
 int /*<<< orphan*/  M_GDTBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct gdt_ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gdt_clear_events () ; 
 int /*<<< orphan*/  gdt_cnt ; 
 int /*<<< orphan*/  gdt_enc32 (int*,int) ; 
 int /*<<< orphan*/  gdt_eval_mapping (int,int*,int*,int*) ; 
 int /*<<< orphan*/  gdt_free_ccb (struct gdt_softc*,struct gdt_ccb*) ; 
 struct gdt_ccb* gdt_get_ccb (struct gdt_softc*) ; 
 scalar_t__ gdt_internal_cmd (struct gdt_softc*,struct gdt_ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  gdt_make_dev (struct gdt_softc*) ; 
 int gdt_stat ; 
 int /*<<< orphan*/  gdtmapmem ; 
 struct gdt_ccb* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sle ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

int
iir_init(struct gdt_softc *gdt)
{
    u_int16_t cdev_cnt;
    int i, id, drv_cyls, drv_hds, drv_secs;
    struct gdt_ccb *gccb;

    GDT_DPRINTF(GDT_D_DEBUG, ("iir_init()\n"));

    gdt->sc_state = GDT_POLLING;
    gdt_clear_events(); 
    bzero(&gdt_stat, sizeof(gdt_statist_t));

    SLIST_INIT(&gdt->sc_free_gccb);
    SLIST_INIT(&gdt->sc_pending_gccb);
    TAILQ_INIT(&gdt->sc_ccb_queue);
    TAILQ_INIT(&gdt->sc_ucmd_queue);

    /* DMA tag for mapping buffers into device visible space. */
    if (bus_dma_tag_create(gdt->sc_parent_dmat, /*alignment*/1, /*boundary*/0,
                           /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
                           /*highaddr*/BUS_SPACE_MAXADDR,
                           /*filter*/NULL, /*filterarg*/NULL,
			   /*maxsize*/DFLTPHYS,
			   /*nsegments*/GDT_MAXSG,
                           /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
                           /*flags*/BUS_DMA_ALLOCNOW,
			   /*lockfunc*/busdma_lock_mutex,
			   /*lockarg*/&gdt->sc_lock,
                           &gdt->sc_buffer_dmat) != 0) {
	device_printf(gdt->sc_devnode,
	    "bus_dma_tag_create(..., gdt->sc_buffer_dmat) failed\n");
        return (1);
    }
    gdt->sc_init_level++;

    /* DMA tag for our ccb structures */
    if (bus_dma_tag_create(gdt->sc_parent_dmat,
			   /*alignment*/1,
			   /*boundary*/0,
                           /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
                           /*highaddr*/BUS_SPACE_MAXADDR,
                           /*filter*/NULL,
			   /*filterarg*/NULL,
                           GDT_MAXCMDS * GDT_SCRATCH_SZ, /* maxsize */
                           /*nsegments*/1,
                           /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			   /*flags*/0, /*lockfunc*/busdma_lock_mutex,
			   /*lockarg*/&gdt->sc_lock,
			   &gdt->sc_gcscratch_dmat) != 0) {
        device_printf(gdt->sc_devnode,
	    "bus_dma_tag_create(...,gdt->sc_gcscratch_dmat) failed\n");
        return (1);
    }
    gdt->sc_init_level++;

    /* Allocation for our ccb scratch area */
    if (bus_dmamem_alloc(gdt->sc_gcscratch_dmat, (void **)&gdt->sc_gcscratch,
                         BUS_DMA_NOWAIT, &gdt->sc_gcscratch_dmamap) != 0) {
        device_printf(gdt->sc_devnode,
	    "bus_dmamem_alloc(...,&gdt->sc_gccbs,...) failed\n");
        return (1);
    }
    gdt->sc_init_level++;

    /* And permanently map them */
    bus_dmamap_load(gdt->sc_gcscratch_dmat, gdt->sc_gcscratch_dmamap,
                    gdt->sc_gcscratch, GDT_MAXCMDS * GDT_SCRATCH_SZ,
                    gdtmapmem, &gdt->sc_gcscratch_busbase, /*flags*/0);
    gdt->sc_init_level++;

    /* Clear them out. */
    bzero(gdt->sc_gcscratch, GDT_MAXCMDS * GDT_SCRATCH_SZ);

    /* Initialize the ccbs */
    gdt->sc_gccbs = malloc(sizeof(struct gdt_ccb) * GDT_MAXCMDS, M_GDTBUF,
        M_NOWAIT | M_ZERO);
    if (gdt->sc_gccbs == NULL) {
        device_printf(gdt->sc_devnode, "no memory for gccbs.\n");
        return (1);
    }
    for (i = GDT_MAXCMDS-1; i >= 0; i--) {
        gccb = &gdt->sc_gccbs[i];
        gccb->gc_cmd_index = i + 2;
        gccb->gc_flags = GDT_GCF_UNUSED;
        gccb->gc_map_flag = FALSE;
        if (bus_dmamap_create(gdt->sc_buffer_dmat, /*flags*/0,
                              &gccb->gc_dmamap) != 0)
            return(1);
        gccb->gc_map_flag = TRUE;
        gccb->gc_scratch = &gdt->sc_gcscratch[GDT_SCRATCH_SZ * i];
        gccb->gc_scratch_busbase = gdt->sc_gcscratch_busbase + GDT_SCRATCH_SZ * i;
	callout_init_mtx(&gccb->gc_timeout, &gdt->sc_lock, 0);
        SLIST_INSERT_HEAD(&gdt->sc_free_gccb, gccb, sle);
    }
    gdt->sc_init_level++;

    /* create the control device */
    gdt->sc_dev = gdt_make_dev(gdt);

    /* allocate ccb for gdt_internal_cmd() */
    mtx_lock(&gdt->sc_lock);
    gccb = gdt_get_ccb(gdt);
    if (gccb == NULL) {
	mtx_unlock(&gdt->sc_lock);
        device_printf(gdt->sc_devnode, "No free command index found\n");
        return (1);
    }
    bzero(gccb->gc_cmd, GDT_CMD_SZ);

    if (!gdt_internal_cmd(gdt, gccb, GDT_SCREENSERVICE, GDT_INIT, 
                          0, 0, 0)) {
        device_printf(gdt->sc_devnode,
	    "Screen service initialization error %d\n", gdt->sc_status);
        gdt_free_ccb(gdt, gccb);
	mtx_unlock(&gdt->sc_lock);
        return (1);
    }

    gdt_internal_cmd(gdt, gccb, GDT_CACHESERVICE, GDT_UNFREEZE_IO,
                     0, 0, 0);

    if (!gdt_internal_cmd(gdt, gccb, GDT_CACHESERVICE, GDT_INIT, 
                          GDT_LINUX_OS, 0, 0)) {
        device_printf(gdt->sc_devnode, "Cache service initialization error %d\n",
               gdt->sc_status);
        gdt_free_ccb(gdt, gccb);
	mtx_unlock(&gdt->sc_lock);
        return (1);
    }
    cdev_cnt = (u_int16_t)gdt->sc_info;
    gdt->sc_fw_vers = gdt->sc_service;

    /* Detect number of buses */
    gdt_enc32(gccb->gc_scratch + GDT_IOC_VERSION, GDT_IOC_NEWEST);
    gccb->gc_scratch[GDT_IOC_LIST_ENTRIES] = GDT_MAXBUS;
    gccb->gc_scratch[GDT_IOC_FIRST_CHAN] = 0;
    gccb->gc_scratch[GDT_IOC_LAST_CHAN] = GDT_MAXBUS - 1;
    gdt_enc32(gccb->gc_scratch + GDT_IOC_LIST_OFFSET, GDT_IOC_HDR_SZ);
    if (gdt_internal_cmd(gdt, gccb, GDT_CACHESERVICE, GDT_IOCTL,
                         GDT_IOCHAN_RAW_DESC, GDT_INVALID_CHANNEL,
                         GDT_IOC_HDR_SZ + GDT_MAXBUS * GDT_RAWIOC_SZ)) {
        gdt->sc_bus_cnt = gccb->gc_scratch[GDT_IOC_CHAN_COUNT];
        for (i = 0; i < gdt->sc_bus_cnt; i++) {
            id = gccb->gc_scratch[GDT_IOC_HDR_SZ +
                                 i * GDT_RAWIOC_SZ + GDT_RAWIOC_PROC_ID];
            gdt->sc_bus_id[i] = id < GDT_MAXID_FC ? id : 0xff;
        }
    } else {
        /* New method failed, use fallback. */
        for (i = 0; i < GDT_MAXBUS; i++) {
            gdt_enc32(gccb->gc_scratch + GDT_GETCH_CHANNEL_NO, i);
            if (!gdt_internal_cmd(gdt, gccb, GDT_CACHESERVICE, GDT_IOCTL,
                                  GDT_SCSI_CHAN_CNT | GDT_L_CTRL_PATTERN,
                                  GDT_IO_CHANNEL | GDT_INVALID_CHANNEL,
                                  GDT_GETCH_SZ)) {
                if (i == 0) {
                    device_printf(gdt->sc_devnode, "Cannot get channel count, "
                           "error %d\n", gdt->sc_status);
                    gdt_free_ccb(gdt, gccb);
		    mtx_unlock(&gdt->sc_lock);
                    return (1);
                }
                break;
            }
            gdt->sc_bus_id[i] =
                (gccb->gc_scratch[GDT_GETCH_SIOP_ID] < GDT_MAXID_FC) ?
                gccb->gc_scratch[GDT_GETCH_SIOP_ID] : 0xff;
        }
        gdt->sc_bus_cnt = i;
    }
    /* add one "virtual" channel for the host drives */
    gdt->sc_virt_bus = gdt->sc_bus_cnt;
    gdt->sc_bus_cnt++;

    if (!gdt_internal_cmd(gdt, gccb, GDT_SCSIRAWSERVICE, GDT_INIT, 
                          0, 0, 0)) {
            device_printf(gdt->sc_devnode,
		"Raw service initialization error %d\n", gdt->sc_status);
            gdt_free_ccb(gdt, gccb);
	    mtx_unlock(&gdt->sc_lock);
            return (1);
    }

    /* Set/get features raw service (scatter/gather) */
    gdt->sc_raw_feat = 0;
    if (gdt_internal_cmd(gdt, gccb, GDT_SCSIRAWSERVICE, GDT_SET_FEAT,
                         GDT_SCATTER_GATHER, 0, 0)) {
        if (gdt_internal_cmd(gdt, gccb, GDT_SCSIRAWSERVICE, GDT_GET_FEAT, 
                             0, 0, 0)) {
            gdt->sc_raw_feat = gdt->sc_info;
            if (!(gdt->sc_info & GDT_SCATTER_GATHER)) {
                panic("%s: Scatter/Gather Raw Service "
		    "required but not supported!\n",
		    device_get_nameunit(gdt->sc_devnode));
                gdt_free_ccb(gdt, gccb);
		mtx_unlock(&gdt->sc_lock);
                return (1);
            }
        }
    }

    /* Set/get features cache service (scatter/gather) */
    gdt->sc_cache_feat = 0;
    if (gdt_internal_cmd(gdt, gccb, GDT_CACHESERVICE, GDT_SET_FEAT, 
                         0, GDT_SCATTER_GATHER, 0)) {
        if (gdt_internal_cmd(gdt, gccb, GDT_CACHESERVICE, GDT_GET_FEAT, 
                             0, 0, 0)) {
            gdt->sc_cache_feat = gdt->sc_info;
            if (!(gdt->sc_info & GDT_SCATTER_GATHER)) {
                panic("%s: Scatter/Gather Cache Service "
		    "required but not supported!\n",
		    device_get_nameunit(gdt->sc_devnode));
                gdt_free_ccb(gdt, gccb);
		mtx_unlock(&gdt->sc_lock);
                return (1);
            }
        }
    }

    /* OEM */
    gdt_enc32(gccb->gc_scratch + GDT_OEM_VERSION, 0x01);
    gdt_enc32(gccb->gc_scratch + GDT_OEM_BUFSIZE, sizeof(gdt_oem_record_t));
    if (gdt_internal_cmd(gdt, gccb, GDT_CACHESERVICE, GDT_IOCTL,
                         GDT_OEM_STR_RECORD, GDT_INVALID_CHANNEL,
                         sizeof(gdt_oem_str_record_t))) {
	    strncpy(gdt->oem_name, ((gdt_oem_str_record_t *)
            gccb->gc_scratch)->text.scsi_host_drive_inquiry_vendor_id, 7);
		gdt->oem_name[7]='\0';
	} else {
		/* Old method, based on PCI ID */
		if (gdt->sc_vendor == INTEL_VENDOR_ID_IIR)
            strcpy(gdt->oem_name,"Intel  ");
        else 
       	    strcpy(gdt->oem_name,"ICP    ");
    }

    /* Scan for cache devices */
    for (i = 0; i < cdev_cnt && i < GDT_MAX_HDRIVES; i++) {
        if (gdt_internal_cmd(gdt, gccb, GDT_CACHESERVICE, GDT_INFO, 
                             i, 0, 0)) {
            gdt->sc_hdr[i].hd_present = 1;
            gdt->sc_hdr[i].hd_size = gdt->sc_info;
            
            /*
             * Evaluate mapping (sectors per head, heads per cyl)
             */
            gdt->sc_hdr[i].hd_size &= ~GDT_SECS32;
            if (gdt->sc_info2 == 0)
                gdt_eval_mapping(gdt->sc_hdr[i].hd_size,
                                 &drv_cyls, &drv_hds, &drv_secs);
            else {
                drv_hds = gdt->sc_info2 & 0xff;
                drv_secs = (gdt->sc_info2 >> 8) & 0xff;
                drv_cyls = gdt->sc_hdr[i].hd_size / drv_hds /
                    drv_secs;
            }
            gdt->sc_hdr[i].hd_heads = drv_hds;
            gdt->sc_hdr[i].hd_secs = drv_secs;
            /* Round the size */
            gdt->sc_hdr[i].hd_size = drv_cyls * drv_hds * drv_secs;
            
            if (gdt_internal_cmd(gdt, gccb, GDT_CACHESERVICE,
                                 GDT_DEVTYPE, i, 0, 0))
                gdt->sc_hdr[i].hd_devtype = gdt->sc_info;
        }
    }
    
    GDT_DPRINTF(GDT_D_INIT, ("dpmem %x %d-bus %d cache device%s\n", 
                             gdt->sc_dpmembase,
                             gdt->sc_bus_cnt, cdev_cnt, 
                             cdev_cnt == 1 ? "" : "s"));
    gdt_free_ccb(gdt, gccb);
    mtx_unlock(&gdt->sc_lock);

    atomic_add_int(&gdt_cnt, 1);
    return (0);
}