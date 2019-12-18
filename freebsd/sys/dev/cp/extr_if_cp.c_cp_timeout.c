#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* board; TYPE_3__* chan; } ;
typedef  TYPE_2__ drv_t ;
typedef  int /*<<< orphan*/  bdrv_t ;
struct TYPE_9__ {int type; } ;
struct TYPE_7__ {scalar_t__ sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_UNLOCK (int /*<<< orphan*/ *) ; 
 int NBRD ; 
 int NCHAN ; 
#define  T_E1 132 
#define  T_E3 131 
#define  T_G703 130 
#define  T_STS1 129 
#define  T_T3 128 
 int /*<<< orphan*/ ** adapter ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),int /*<<< orphan*/ ) ; 
 TYPE_2__** channel ; 
 scalar_t__ cp_destroy ; 
 int /*<<< orphan*/  cp_e1_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_e3_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_g703_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  hz ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  timeout_handle ; 

__attribute__((used)) static void cp_timeout (void *arg)
{
	drv_t *d;
	int s, i, k;

	for (i = 0; i < NBRD; ++i) {
		if (adapter[i] == NULL)
			continue;
		for (k = 0; k < NCHAN; ++k) {
			s = splimp ();
			if (cp_destroy) {
				splx (s);
				return;
			}
			d = channel[i * NCHAN + k];
			if (!d) {
				splx (s);
				continue;
			}
			CP_LOCK ((bdrv_t *)d->board->sys);
			switch (d->chan->type) {
			case T_G703:
				cp_g703_timer (d->chan);
				break;
			case T_E1:
				cp_e1_timer (d->chan);
				break;
			case T_E3:
			case T_T3:
			case T_STS1:
				cp_e3_timer (d->chan);
				break;
			default:
				break;
			}
			CP_UNLOCK ((bdrv_t *)d->board->sys);
			splx (s);
		}
	}
	s = splimp ();
	if (!cp_destroy)
		callout_reset (&timeout_handle, hz, cp_timeout, 0);
	splx (s);
}