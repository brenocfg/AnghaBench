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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {int /*<<< orphan*/  ts_teken; } ;
typedef  TYPE_2__ teken_stat ;
struct TYPE_7__ {TYPE_1__* sc; TYPE_2__* ts; } ;
typedef  TYPE_3__ scr_stat ;
struct TYPE_5__ {int /*<<< orphan*/  write_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  teken_input (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
scteken_puts(scr_stat *scp, u_char *buf, int len)
{
	teken_stat *ts = scp->ts;

	scp->sc->write_in_progress++;
	teken_input(&ts->ts_teken, buf, len);
	scp->sc->write_in_progress--;
}