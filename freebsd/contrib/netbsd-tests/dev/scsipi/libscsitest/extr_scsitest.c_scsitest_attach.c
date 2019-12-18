#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int adapt_nchannels; int adapt_max_periph; int adapt_openings; int chan_ntargets; int chan_nluns; struct TYPE_3__* chan_adapter; int /*<<< orphan*/  chan_flags; scalar_t__ chan_id; int /*<<< orphan*/ * chan_bustype; int /*<<< orphan*/  adapt_dev; int /*<<< orphan*/  adapt_minphys; int /*<<< orphan*/  adapt_request; } ;
struct scsitest {TYPE_1__ sc_channel; TYPE_1__ sc_adapter; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCSIPI_CHAN_NOSETTLE ; 
 int /*<<< orphan*/  aprint_naive (char*) ; 
 int /*<<< orphan*/  aprint_normal (char*) ; 
 int /*<<< orphan*/  config_found_ia (int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct scsitest* device_private (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  minphys ; 
 int /*<<< orphan*/  scsi_bustype ; 
 int /*<<< orphan*/  scsiprint ; 
 int /*<<< orphan*/  scsitest_request ; 

void
scsitest_attach(device_t parent, device_t self, void *aux)
{
	struct scsitest *sc = device_private(self);
	
	aprint_naive("\n");
	aprint_normal("\n");

	memset(&sc->sc_adapter, 0, sizeof(sc->sc_adapter));
	sc->sc_adapter.adapt_nchannels = 1;
	sc->sc_adapter.adapt_request = scsitest_request;
	sc->sc_adapter.adapt_minphys = minphys;
	sc->sc_adapter.adapt_dev = self;
	sc->sc_adapter.adapt_max_periph = 1;
	sc->sc_adapter.adapt_openings = 1;

	memset(&sc->sc_channel, 0, sizeof(sc->sc_channel));
	sc->sc_channel.chan_bustype = &scsi_bustype;
	sc->sc_channel.chan_ntargets = 2;
	sc->sc_channel.chan_nluns = 1;
	sc->sc_channel.chan_id = 0;
	sc->sc_channel.chan_flags = SCSIPI_CHAN_NOSETTLE;
	sc->sc_channel.chan_adapter = &sc->sc_adapter;

	config_found_ia(self, "scsi", &sc->sc_channel, scsiprint);
}