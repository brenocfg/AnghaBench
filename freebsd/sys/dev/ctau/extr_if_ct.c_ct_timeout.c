#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bd; TYPE_2__* chan; } ;
typedef  TYPE_1__ drv_t ;
typedef  int /*<<< orphan*/  bdrv_t ;
struct TYPE_5__ {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CT_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ M_G703 ; 
 int NCHAN ; 
 int NCTAU ; 
 int /*<<< orphan*/ ** adapter ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),int /*<<< orphan*/ ) ; 
 TYPE_1__** channel ; 
 int /*<<< orphan*/  ct_g703_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  hz ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  timeout_handle ; 

__attribute__((used)) static void ct_timeout (void *arg)
{
	drv_t *d;
	int s, i, k;

	for (i = 0; i < NCTAU; ++i) {
		if (adapter[i] == NULL)
			continue;
		for (k = 0; k < NCHAN; k++) {
			d = channel[i * NCHAN + k];
			if (! d)
				continue;
			if (d->chan->mode != M_G703)
				continue;
			s = splimp ();
			CT_LOCK ((bdrv_t *)d->bd);
			ct_g703_timer (d->chan);
			CT_UNLOCK ((bdrv_t *)d->bd);
			splx (s);
		}
	}
	
	callout_reset (&timeout_handle, hz, ct_timeout, 0);
}