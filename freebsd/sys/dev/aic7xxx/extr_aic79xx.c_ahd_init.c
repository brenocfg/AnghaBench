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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_int ;
struct target_cmd {int dummy; } ;
struct hardware_scb {int /*<<< orphan*/  hscb_busaddr; } ;
struct TYPE_2__ {scalar_t__ busaddr; scalar_t__ vaddr; int /*<<< orphan*/  dmamap; } ;
struct ahd_softc {int stack_size; int flags; int unit; int features; int bugs; int* overrun_buf; int /*<<< orphan*/  stat_timer; int /*<<< orphan*/  init_level; struct hardware_scb* next_queued_hscb; TYPE_1__ shared_data_map; TYPE_1__* next_queued_hscb_map; struct target_cmd* targetcmds; struct ahd_completion* qoutfifo; int /*<<< orphan*/  shared_data_dmat; int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  buffer_dmat; int /*<<< orphan*/ * saved_stack; } ;
struct ahd_completion {int dummy; } ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int AHD_39BIT_ADDRESSING ; 
 int /*<<< orphan*/  AHD_ASSERT_MODES (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AHD_CORRECTABLE_ERROR (struct ahd_softc*) ; 
 int AHD_CURRENT_SENSING ; 
 int AHD_DEBUG_SEQUENCER ; 
 int AHD_INITIATORROLE ; 
 int /*<<< orphan*/  AHD_MAXTRANSFER_SIZE ; 
 int /*<<< orphan*/  AHD_MODE_SCSI_MSK ; 
 int AHD_NSEG ; 
 int AHD_PKT_BITBUCKET_BUG ; 
 size_t AHD_QOUT_SIZE ; 
 int AHD_RESET_BUS_A ; 
 int AHD_SCB_MAX ; 
 int AHD_SEQUENCER_DEBUG ; 
 int AHD_SHOW_TERMCTL ; 
 int /*<<< orphan*/  AHD_STAT_UPDATE_MS ; 
 int AHD_TARGETMODE ; 
 int AHD_TMODE_CMDS ; 
 int AHD_TMODE_ENABLE ; 
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 scalar_t__ BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  CURSENSE_ENB ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FLXADDR_CURRENT_STAT ; 
 int /*<<< orphan*/  FLXADDR_FLEXSTAT ; 
 int /*<<< orphan*/  FLXADDR_ROMSTAT_CURSENSECTL ; 
#define  FLX_CSTAT_INVALID 131 
 int FLX_CSTAT_MASK ; 
#define  FLX_CSTAT_OKAY 130 
#define  FLX_CSTAT_OVER 129 
 int FLX_CSTAT_SHIFT ; 
#define  FLX_CSTAT_UNDER 128 
 int FLX_FSTAT_BUSY ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int PAGE_SIZE ; 
 scalar_t__ PKT_OVERRUN_BUFSIZE ; 
 int /*<<< orphan*/  ahd_chip_init (struct ahd_softc*) ; 
 int ahd_debug ; 
 int /*<<< orphan*/  ahd_dmamap_cb ; 
 scalar_t__ ahd_init_scbdata (struct ahd_softc*) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_platform_init (struct ahd_softc*) ; 
 int ahd_probe_stack_size (struct ahd_softc*) ; 
 int ahd_read_flexport (struct ahd_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ahd_restart (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_stat_timer ; 
 int ahd_write_flexport (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ aic_dma_tag_create (struct ahd_softc*,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aic_dmamap_load (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,size_t,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ aic_dmamem_alloc (struct ahd_softc*,int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aic_htole32 (scalar_t__) ; 
 int /*<<< orphan*/  aic_timer_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ahd_softc*) ; 
 int /*<<< orphan*/  bootverbose ; 
 char** channel_strings ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char** termstat_strings ; 

int
ahd_init(struct ahd_softc *ahd)
{
	uint8_t		*next_vaddr;
	bus_addr_t	 next_baddr;
	size_t		 driver_data_size;
	int		 i;
	int		 error;
	u_int		 warn_user;
	uint8_t		 current_sensing;
	uint8_t		 fstat;

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);

	ahd->stack_size = ahd_probe_stack_size(ahd);
	ahd->saved_stack = malloc(ahd->stack_size * sizeof(uint16_t),
				  M_DEVBUF, M_NOWAIT);
	if (ahd->saved_stack == NULL)
		return (ENOMEM);

	/*
	 * Verify that the compiler hasn't over-agressively
	 * padded important structures.
	 */
	if (sizeof(struct hardware_scb) != 64)
		panic("Hardware SCB size is incorrect");

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_DEBUG_SEQUENCER) != 0)
		ahd->flags |= AHD_SEQUENCER_DEBUG;
#endif

	/*
	 * Default to allowing initiator operations.
	 */
	ahd->flags |= AHD_INITIATORROLE;

	/*
	 * Only allow target mode features if this unit has them enabled.
	 */
	if ((AHD_TMODE_ENABLE & (0x1 << ahd->unit)) == 0)
		ahd->features &= ~AHD_TARGETMODE;

#ifndef __linux__
	/* DMA tag for mapping buffers into device visible space. */
	if (aic_dma_tag_create(ahd, ahd->parent_dmat, /*alignment*/1,
			       /*boundary*/BUS_SPACE_MAXADDR_32BIT + 1,
			       /*lowaddr*/ahd->flags & AHD_39BIT_ADDRESSING
					? (bus_addr_t)0x7FFFFFFFFFULL
					: BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/NULL, /*filterarg*/NULL,
			       /*maxsize*/(AHD_NSEG - 1) * PAGE_SIZE,
			       /*nsegments*/AHD_NSEG,
			       /*maxsegsz*/AHD_MAXTRANSFER_SIZE,
			       /*flags*/BUS_DMA_ALLOCNOW,
			       &ahd->buffer_dmat) != 0) {
		return (ENOMEM);
	}
#endif

	ahd->init_level++;

	/*
	 * DMA tag for our command fifos and other data in system memory
	 * the card's sequencer must be able to access.  For initiator
	 * roles, we need to allocate space for the qoutfifo.  When providing
	 * for the target mode role, we must additionally provide space for
	 * the incoming target command fifo.
	 */
	driver_data_size = AHD_SCB_MAX * sizeof(*ahd->qoutfifo)
			 + sizeof(struct hardware_scb);
	if ((ahd->features & AHD_TARGETMODE) != 0)
		driver_data_size += AHD_TMODE_CMDS * sizeof(struct target_cmd);
	if ((ahd->bugs & AHD_PKT_BITBUCKET_BUG) != 0)
		driver_data_size += PKT_OVERRUN_BUFSIZE;
	if (aic_dma_tag_create(ahd, ahd->parent_dmat, /*alignment*/1,
			       /*boundary*/BUS_SPACE_MAXADDR_32BIT + 1,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/NULL, /*filterarg*/NULL,
			       driver_data_size,
			       /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*flags*/0, &ahd->shared_data_dmat) != 0) {
		return (ENOMEM);
	}

	ahd->init_level++;

	/* Allocation of driver data */
	if (aic_dmamem_alloc(ahd, ahd->shared_data_dmat,
			     (void **)&ahd->shared_data_map.vaddr,
			     BUS_DMA_NOWAIT | BUS_DMA_COHERENT,
			     &ahd->shared_data_map.dmamap) != 0) {
		return (ENOMEM);
	}

	ahd->init_level++;

	/* And permanently map it in */
	aic_dmamap_load(ahd, ahd->shared_data_dmat, ahd->shared_data_map.dmamap,
			ahd->shared_data_map.vaddr, driver_data_size,
			ahd_dmamap_cb, &ahd->shared_data_map.busaddr,
			/*flags*/0);
	ahd->qoutfifo = (struct ahd_completion *)ahd->shared_data_map.vaddr;
	next_vaddr = (uint8_t *)&ahd->qoutfifo[AHD_QOUT_SIZE];
	next_baddr = ahd->shared_data_map.busaddr
		   + AHD_QOUT_SIZE*sizeof(struct ahd_completion);
	if ((ahd->features & AHD_TARGETMODE) != 0) {
		ahd->targetcmds = (struct target_cmd *)next_vaddr;
		next_vaddr += AHD_TMODE_CMDS * sizeof(struct target_cmd);
		next_baddr += AHD_TMODE_CMDS * sizeof(struct target_cmd);
	}

	if ((ahd->bugs & AHD_PKT_BITBUCKET_BUG) != 0) {
		ahd->overrun_buf = next_vaddr;
		next_vaddr += PKT_OVERRUN_BUFSIZE;
		next_baddr += PKT_OVERRUN_BUFSIZE;
	}

	/*
	 * We need one SCB to serve as the "next SCB".  Since the
	 * tag identifier in this SCB will never be used, there is
	 * no point in using a valid HSCB tag from an SCB pulled from
	 * the standard free pool.  So, we allocate this "sentinel"
	 * specially from the DMA safe memory chunk used for the QOUTFIFO.
	 */
	ahd->next_queued_hscb = (struct hardware_scb *)next_vaddr;
	ahd->next_queued_hscb_map = &ahd->shared_data_map;
	ahd->next_queued_hscb->hscb_busaddr = aic_htole32(next_baddr);

	ahd->init_level++;

	/* Allocate SCB data now that buffer_dmat is initialized */
	if (ahd_init_scbdata(ahd) != 0)
		return (ENOMEM);

	if ((ahd->flags & AHD_INITIATORROLE) == 0)
		ahd->flags &= ~AHD_RESET_BUS_A;

	/*
	 * Before committing these settings to the chip, give
	 * the OSM one last chance to modify our configuration.
	 */
	ahd_platform_init(ahd);

	/* Bring up the chip. */
	ahd_chip_init(ahd);

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);

	if ((ahd->flags & AHD_CURRENT_SENSING) == 0)
		goto init_done;

	/*
	 * Verify termination based on current draw and
	 * warn user if the bus is over/under terminated.
	 */
	error = ahd_write_flexport(ahd, FLXADDR_ROMSTAT_CURSENSECTL,
				   CURSENSE_ENB);
	if (error != 0) {
		printf("%s: current sensing timeout 1\n", ahd_name(ahd));
		goto init_done;
	}
	for (i = 20, fstat = FLX_FSTAT_BUSY;
	     (fstat & FLX_FSTAT_BUSY) != 0 && i; i--) {
		error = ahd_read_flexport(ahd, FLXADDR_FLEXSTAT, &fstat);
		if (error != 0) {
			printf("%s: current sensing timeout 2\n",
			       ahd_name(ahd));
			goto init_done;
		}
	}
	if (i == 0) {
		printf("%s: Timedout during current-sensing test\n",
		       ahd_name(ahd));
		goto init_done;
	}

	/* Latch Current Sensing status. */
	error = ahd_read_flexport(ahd, FLXADDR_CURRENT_STAT, &current_sensing);
	if (error != 0) {
		printf("%s: current sensing timeout 3\n", ahd_name(ahd));
		goto init_done;
	}

	/* Diable current sensing. */
	ahd_write_flexport(ahd, FLXADDR_ROMSTAT_CURSENSECTL, 0);

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_TERMCTL) != 0) {
		printf("%s: current_sensing == 0x%x\n",
		       ahd_name(ahd), current_sensing);
	}
#endif
	warn_user = 0;
	for (i = 0; i < 4; i++, current_sensing >>= FLX_CSTAT_SHIFT) {
		u_int term_stat;

		term_stat = (current_sensing & FLX_CSTAT_MASK);
		switch (term_stat) {
		case FLX_CSTAT_OVER:
		case FLX_CSTAT_UNDER:
			warn_user++;
		case FLX_CSTAT_INVALID:
		case FLX_CSTAT_OKAY:
			if (warn_user == 0 && bootverbose == 0)
				break;
			printf("%s: %s Channel %s\n", ahd_name(ahd),
			       channel_strings[i], termstat_strings[term_stat]);
			break;
		}
	}
	if (warn_user) {
		printf("%s: WARNING. Termination is not configured correctly.\n"
		       "%s: WARNING. SCSI bus operations may FAIL.\n",
		       ahd_name(ahd), ahd_name(ahd));
		AHD_CORRECTABLE_ERROR(ahd);
	}
init_done:
	ahd_restart(ahd);
	aic_timer_reset(&ahd->stat_timer, AHD_STAT_UPDATE_MS,
			ahd_stat_timer, ahd);
	return (0);
}