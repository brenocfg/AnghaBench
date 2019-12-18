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
struct TYPE_3__ {scalar_t__ sys; } ;
typedef  TYPE_1__ cp_board_t ;
typedef  int /*<<< orphan*/  bdrv_t ;

/* Variables and functions */
 int /*<<< orphan*/  CP_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ cp_destroy ; 
 int /*<<< orphan*/  cp_led (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void cp_led_off (void *arg)
{
	cp_board_t *b = arg;
	bdrv_t *bd = (bdrv_t *) b->sys;
	int s;
	s = splimp ();
	if (cp_destroy) {
		splx (s);
		return;
	}
	CP_LOCK (bd);
	cp_led (b, 0);
	CP_UNLOCK (bd);
	splx (s);
}