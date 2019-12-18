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
struct sc_pcminfo {int chnum; struct sc_chinfo* chan; } ;
struct sc_info {int /*<<< orphan*/  dev; } ;
struct sc_chinfo {scalar_t__ run; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 struct sc_pcminfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hdspe_running(struct sc_info *sc)
{
	struct sc_pcminfo *scp;
	struct sc_chinfo *ch;
	device_t *devlist;
	int devcount;
	int i, j;
	int err;

	if ((err = device_get_children(sc->dev, &devlist, &devcount)) != 0)
		goto bad;

	for (i = 0; i < devcount; i++) {
		scp = device_get_ivars(devlist[i]);
		for (j = 0; j < scp->chnum; j++) {
			ch = &scp->chan[j];
			if (ch->run)
				goto bad;
		}
	}

	free(devlist, M_TEMP);

	return (0);
bad:

#if 0
	device_printf(sc->dev, "hdspe is running\n");
#endif

	free(devlist, M_TEMP);

	return (1);
}