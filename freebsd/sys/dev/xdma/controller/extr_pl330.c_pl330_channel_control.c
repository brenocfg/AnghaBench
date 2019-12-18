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
struct TYPE_3__ {scalar_t__ chan; } ;
typedef  TYPE_1__ xdma_channel_t ;
struct pl330_softc {int dummy; } ;
struct pl330_channel {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  XDMA_CMD_BEGIN 130 
#define  XDMA_CMD_PAUSE 129 
#define  XDMA_CMD_TERMINATE 128 
 struct pl330_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pl330_channel_control(device_t dev, xdma_channel_t *xchan, int cmd)
{
	struct pl330_channel *chan;
	struct pl330_softc *sc;

	sc = device_get_softc(dev);

	chan = (struct pl330_channel *)xchan->chan;

	switch (cmd) {
	case XDMA_CMD_BEGIN:
	case XDMA_CMD_TERMINATE:
	case XDMA_CMD_PAUSE:
		/* TODO: implement me */
		return (-1);
	}

	return (0);
}