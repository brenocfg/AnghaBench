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
struct sb_info {uintptr_t bd_id; uintptr_t bd_flags; int /*<<< orphan*/  bufsize; int /*<<< orphan*/  drq; int /*<<< orphan*/  irq; int /*<<< orphan*/  io_base; int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  ih; int /*<<< orphan*/  parent_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_READ_IVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t*) ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_24BIT ; 
 int ENXIO ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int /*<<< orphan*/  PCM_KLDSTRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_DEFAULT_BUFSZ ; 
 int SD_F_SIMPLEX ; 
 int SND_STATUSLEN ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct sb_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sb_info*) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sb_info*) ; 
 int /*<<< orphan*/  pcm_getbuffersize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int pcm_getflags (int /*<<< orphan*/ ) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct sb_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setflags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 
 scalar_t__ sb_alloc_resources (struct sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_intr ; 
 int /*<<< orphan*/  sb_release_resources (struct sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ sb_reset_dsp (struct sb_info*) ; 
 int /*<<< orphan*/  sbchan_class ; 
 int /*<<< orphan*/  sbmix_mixer_class ; 
 int /*<<< orphan*/  sbpromix_mixer_class ; 
 int /*<<< orphan*/  snd_sb8 ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sb_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sb_attach(device_t dev)
{
    	struct sb_info *sb;
    	char status[SND_STATUSLEN];
	uintptr_t ver;

    	sb = malloc(sizeof(*sb), M_DEVBUF, M_WAITOK | M_ZERO);
	sb->parent_dev = device_get_parent(dev);
	BUS_READ_IVAR(device_get_parent(dev), dev, 1, &ver);
	sb->bd_id = ver & 0x0000ffff;
	sb->bd_flags = (ver & 0xffff0000) >> 16;
	sb->bufsize = pcm_getbuffersize(dev, 4096, SB_DEFAULT_BUFSZ, 65536);

    	if (sb_alloc_resources(sb, dev))
		goto no;
    	if (sb_reset_dsp(sb))
		goto no;
    	if (mixer_init(dev, (sb->bd_id < 0x300)? &sbmix_mixer_class : &sbpromix_mixer_class, sb))
		goto no;
	if (snd_setup_intr(dev, sb->irq, 0, sb_intr, sb, &sb->ih))
		goto no;

	pcm_setflags(dev, pcm_getflags(dev) | SD_F_SIMPLEX);

    	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev), /*alignment*/2,
			/*boundary*/0,
			/*lowaddr*/BUS_SPACE_MAXADDR_24BIT,
			/*highaddr*/BUS_SPACE_MAXADDR,
			/*filter*/NULL, /*filterarg*/NULL,
			/*maxsize*/sb->bufsize, /*nsegments*/1,
			/*maxsegz*/0x3ffff, /*flags*/0,
			/*lockfunc*/busdma_lock_mutex, /*lockarg*/&Giant,
			&sb->parent_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto no;
    	}

    	snprintf(status, SND_STATUSLEN, "at io 0x%jx irq %jd drq %jd bufsz %u %s",
    	     	rman_get_start(sb->io_base), rman_get_start(sb->irq),
		rman_get_start(sb->drq), sb->bufsize, PCM_KLDSTRING(snd_sb8));

    	if (pcm_register(dev, sb, 1, 1))
		goto no;
	pcm_addchan(dev, PCMDIR_REC, &sbchan_class, sb);
	pcm_addchan(dev, PCMDIR_PLAY, &sbchan_class, sb);

    	pcm_setstatus(dev, status);

    	return 0;

no:
    	sb_release_resources(sb, dev);
    	return ENXIO;
}