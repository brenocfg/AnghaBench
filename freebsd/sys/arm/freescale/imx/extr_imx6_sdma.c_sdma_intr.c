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
struct sdma_softc {struct sdma_channel* channel; } ;
struct sdma_conf {int num_bd; int /*<<< orphan*/  ih_user; int /*<<< orphan*/  (* ih ) (int /*<<< orphan*/ ,int) ;} ;
struct sdma_channel {struct sdma_buffer_descriptor* bd; struct sdma_conf* conf; } ;
struct TYPE_2__ {int status; } ;
struct sdma_buffer_descriptor {TYPE_1__ mode; } ;

/* Variables and functions */
 int BD_DONE ; 
 int BD_RROR ; 
 int READ4 (struct sdma_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMAARM_HSTART ; 
 int /*<<< orphan*/  SDMAARM_INTR ; 
 int SDMA_N_CHANNELS ; 
 int /*<<< orphan*/  WRITE4 (struct sdma_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sdma_intr(void *arg)
{
	struct sdma_buffer_descriptor *bd;
	struct sdma_channel *channel;
	struct sdma_conf *conf;
	struct sdma_softc *sc;
	int pending;
	int i;
	int j;

	sc = arg;

	pending = READ4(sc, SDMAARM_INTR);

	/* Ack intr */
	WRITE4(sc, SDMAARM_INTR, pending);

	for (i = 0; i < SDMA_N_CHANNELS; i++) {
		if ((pending & (1 << i)) == 0)
			continue;
		channel = &sc->channel[i];
		conf = channel->conf;
		if (!conf)
			continue;
		for (j = 0; j < conf->num_bd; j++) {
			bd = &channel->bd[j];
			bd->mode.status |= BD_DONE;
			if (bd->mode.status & BD_RROR)
				printf("sDMA error\n");
		}

		conf->ih(conf->ih_user, 1);

		WRITE4(sc, SDMAARM_HSTART, (1 << i));
	}
}