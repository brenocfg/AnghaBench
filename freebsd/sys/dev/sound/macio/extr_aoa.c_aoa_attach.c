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
struct aoa_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  status ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOA_BUFFER_SIZE ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int SND_STATUSLEN ; 
 int /*<<< orphan*/  aoa_chan_class ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct aoa_softc*) ; 
 int pcm_getbuffersize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct aoa_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

int
aoa_attach(void *xsc)
{
	char status[SND_STATUSLEN];
	struct aoa_softc *sc;
	device_t self;
	int err;

	sc = xsc;
	self = sc->sc_dev;

	if (pcm_register(self, sc, 1, 0))
		return (ENXIO);

	err = pcm_getbuffersize(self, AOA_BUFFER_SIZE, AOA_BUFFER_SIZE,
	    AOA_BUFFER_SIZE);
	DPRINTF(("pcm_getbuffersize returned %d\n", err));

	pcm_addchan(self, PCMDIR_PLAY, &aoa_chan_class, sc);

	snprintf(status, sizeof(status), "at %s", ofw_bus_get_name(self)); 
	pcm_setstatus(self, status);

	return (0);
}