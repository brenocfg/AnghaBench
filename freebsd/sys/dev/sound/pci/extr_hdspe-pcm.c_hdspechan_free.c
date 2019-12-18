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
struct sc_pcminfo {int /*<<< orphan*/  dev; struct sc_info* sc; } ;
struct sc_info {int /*<<< orphan*/  lock; } ;
struct sc_chinfo {int /*<<< orphan*/ * data; struct sc_pcminfo* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_HDSPE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hdspechan_free(kobj_t obj, void *data)
{
	struct sc_pcminfo *scp;
	struct sc_chinfo *ch;
	struct sc_info *sc;

	ch = data;
	scp = ch->parent;
	sc = scp->sc;

#if 0
	device_printf(scp->dev, "hdspechan_free()\n");
#endif

	snd_mtxlock(sc->lock);
	if (ch->data != NULL) {
		free(ch->data, M_HDSPE);
		ch->data = NULL;
	}
	snd_mtxunlock(sc->lock);

	return (0);
}