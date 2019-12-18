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
struct mss_info {int bd_id; int /*<<< orphan*/  bufsize; int /*<<< orphan*/  irq; int /*<<< orphan*/  io_base; int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  ih; int /*<<< orphan*/  drq2; int /*<<< orphan*/  drq1; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_24BIT ; 
 int DV_F_TRUE_MSS ; 
 int ENXIO ; 
 int /*<<< orphan*/  Giant ; 
#define  MD_OPTI931 128 
 int MD_YM0020 ; 
 int /*<<< orphan*/  MSS_DEFAULT_BUFSZ ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int SD_F_SIMPLEX ; 
 int SND_STATUSLEN ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int io_rd (struct mss_info*,int) ; 
 int /*<<< orphan*/  io_wr (struct mss_info*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mss_info*) ; 
 int /*<<< orphan*/  mss_alloc_resources (struct mss_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mss_init (struct mss_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mss_intr ; 
 int /*<<< orphan*/  mss_release_resources (struct mss_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msschan_class ; 
 int /*<<< orphan*/  mssmix_mixer_class ; 
 int /*<<< orphan*/  opti931_intr ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mss_info*) ; 
 int /*<<< orphan*/  pcm_getbuffersize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int pcm_getflags (int /*<<< orphan*/ ) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct mss_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setflags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 size_t rman_get_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mss_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,size_t,...) ; 
 int /*<<< orphan*/  ymmix_mixer_class ; 

__attribute__((used)) static int
mss_doattach(device_t dev, struct mss_info *mss)
{
    	int pdma, rdma, flags = device_get_flags(dev);
    	char status[SND_STATUSLEN], status2[SND_STATUSLEN];

	mss->lock = snd_mtxcreate(device_get_nameunit(dev), "snd_mss softc");
	mss->bufsize = pcm_getbuffersize(dev, 4096, MSS_DEFAULT_BUFSZ, 65536);
    	if (!mss_alloc_resources(mss, dev)) goto no;
    	mss_init(mss, dev);
	pdma = rman_get_start(mss->drq1);
	rdma = rman_get_start(mss->drq2);
    	if (flags & DV_F_TRUE_MSS) {
		/* has IRQ/DMA registers, set IRQ and DMA addr */
		static char     interrupt_bits[12] =
	    	{-1, -1, -1, -1, -1, 0x28, -1, 0x08, -1, 0x10, 0x18, 0x20};
		static char     pdma_bits[4] =  {1, 2, -1, 3};
		static char	valid_rdma[4] = {1, 0, -1, 0};
		char		bits;

		if (!mss->irq || (bits = interrupt_bits[rman_get_start(mss->irq)]) == -1)
			goto no;
		io_wr(mss, 0, bits | 0x40);	/* config port */
		if ((io_rd(mss, 3) & 0x40) == 0) device_printf(dev, "IRQ Conflict?\n");
		/* Write IRQ+DMA setup */
		if (pdma_bits[pdma] == -1) goto no;
		bits |= pdma_bits[pdma];
		if (pdma != rdma) {
	    		if (rdma == valid_rdma[pdma]) bits |= 4;
	    		else {
				printf("invalid dual dma config %d:%d\n", pdma, rdma);
				goto no;
	    		}
		}
		io_wr(mss, 0, bits);
		printf("drq/irq conf %x\n", io_rd(mss, 0));
    	}
    	mixer_init(dev, (mss->bd_id == MD_YM0020)? &ymmix_mixer_class : &mssmix_mixer_class, mss);
    	switch (mss->bd_id) {
    	case MD_OPTI931:
		snd_setup_intr(dev, mss->irq, 0, opti931_intr, mss, &mss->ih);
		break;
    	default:
		snd_setup_intr(dev, mss->irq, 0, mss_intr, mss, &mss->ih);
    	}
    	if (pdma == rdma)
		pcm_setflags(dev, pcm_getflags(dev) | SD_F_SIMPLEX);
    	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev), /*alignment*/2,
			/*boundary*/0,
			/*lowaddr*/BUS_SPACE_MAXADDR_24BIT,
			/*highaddr*/BUS_SPACE_MAXADDR,
			/*filter*/NULL, /*filterarg*/NULL,
			/*maxsize*/mss->bufsize, /*nsegments*/1,
			/*maxsegz*/0x3ffff, /*flags*/0,
			/*lockfunc*/busdma_lock_mutex, /*lockarg*/&Giant,
			&mss->parent_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto no;
    	}

    	if (pdma != rdma)
		snprintf(status2, SND_STATUSLEN, ":%d", rdma);
	else
		status2[0] = '\0';

    	snprintf(status, SND_STATUSLEN, "at io 0x%jx irq %jd drq %d%s bufsz %u",
    	     	rman_get_start(mss->io_base), rman_get_start(mss->irq), pdma, status2, mss->bufsize);

    	if (pcm_register(dev, mss, 1, 1)) goto no;
    	pcm_addchan(dev, PCMDIR_REC, &msschan_class, mss);
    	pcm_addchan(dev, PCMDIR_PLAY, &msschan_class, mss);
    	pcm_setstatus(dev, status);

    	return 0;
no:
    	mss_release_resources(mss, dev);
    	return ENXIO;
}