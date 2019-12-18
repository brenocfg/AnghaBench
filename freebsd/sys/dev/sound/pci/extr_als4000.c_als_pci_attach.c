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
struct sc_info {int /*<<< orphan*/  irq; int /*<<< orphan*/  reg; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ PCI_POWERSTATE_D0 ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int /*<<< orphan*/  PCM_KLDSTRING (int /*<<< orphan*/ ) ; 
 int SND_STATUSLEN ; 
 scalar_t__ als_init (struct sc_info*) ; 
 int /*<<< orphan*/  als_mixer_class ; 
 int /*<<< orphan*/  als_resource_free (int /*<<< orphan*/ ,struct sc_info*) ; 
 scalar_t__ als_resource_grab (int /*<<< orphan*/ ,struct sc_info*) ; 
 int /*<<< orphan*/  alspchan_class ; 
 int /*<<< orphan*/  alsrchan_class ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct sc_info*,int /*<<< orphan*/ ) ; 
 struct sc_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_info*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_powerstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_powerstate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_info*) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct sc_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_als4000 ; 
 int /*<<< orphan*/  snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
als_pci_attach(device_t dev)
{
	struct sc_info *sc;
	char status[SND_STATUSLEN];

	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);
	sc->lock = snd_mtxcreate(device_get_nameunit(dev), "snd_als4000 softc");
	sc->dev = dev;

	pci_enable_busmaster(dev);
	/*
	 * By default the power to the various components on the
         * ALS4000 is entirely controlled by the pci powerstate.  We
         * could attempt finer grained control by setting GCR6.31.
	 */
	if (pci_get_powerstate(dev) != PCI_POWERSTATE_D0) {
		/* Reset the power state. */
		device_printf(dev, "chip is in D%d power mode "
			      "-- setting to D0\n", pci_get_powerstate(dev));
		pci_set_powerstate(dev, PCI_POWERSTATE_D0);
	}

	if (als_resource_grab(dev, sc)) {
		device_printf(dev, "failed to allocate resources\n");
		goto bad_attach;
	}

	if (als_init(sc)) {
		device_printf(dev, "failed to initialize hardware\n");
		goto bad_attach;
	}

	if (mixer_init(dev, &als_mixer_class, sc)) {
		device_printf(dev, "failed to initialize mixer\n");
		goto bad_attach;
	}

	if (pcm_register(dev, sc, 1, 1)) {
		device_printf(dev, "failed to register pcm entries\n");
		goto bad_attach;
	}

	pcm_addchan(dev, PCMDIR_PLAY, &alspchan_class, sc);
	pcm_addchan(dev, PCMDIR_REC,  &alsrchan_class, sc);

	snprintf(status, SND_STATUSLEN, "at io 0x%jx irq %jd %s",
		 rman_get_start(sc->reg), rman_get_start(sc->irq),PCM_KLDSTRING(snd_als4000));
	pcm_setstatus(dev, status);
	return 0;

 bad_attach:
	als_resource_free(dev, sc);
	free(sc, M_DEVBUF);
	return ENXIO;
}