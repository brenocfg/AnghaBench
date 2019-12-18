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
struct TYPE_3__ {int /*<<< orphan*/ * sys; } ;
typedef  TYPE_1__ cx_board_t ;
typedef  int /*<<< orphan*/  bdrv_t ;

/* Variables and functions */
 int /*<<< orphan*/  CX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CX_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx_led (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void cx_led_off (void *arg)
{
	cx_board_t *b = arg;
	bdrv_t *bd = b->sys;
	int s;

	s = splhigh ();
	CX_LOCK (bd);
	cx_led (b, 0);
	CX_UNLOCK (bd);
	splx (s);
}