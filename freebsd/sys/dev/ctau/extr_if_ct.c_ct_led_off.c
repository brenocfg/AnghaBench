#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * bd; } ;
typedef  TYPE_2__ drv_t ;
struct TYPE_7__ {TYPE_1__* chan; } ;
typedef  TYPE_3__ ct_board_t ;
typedef  int /*<<< orphan*/  bdrv_t ;
struct TYPE_5__ {scalar_t__ sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CT_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ct_led (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void ct_led_off (void *arg)
{
	ct_board_t *b = arg;
	bdrv_t *bd = ((drv_t *)b->chan->sys)->bd;
	int s = splimp ();

	CT_LOCK (bd);
	ct_led (b, 0);
	CT_UNLOCK (bd);
	splx (s);
}