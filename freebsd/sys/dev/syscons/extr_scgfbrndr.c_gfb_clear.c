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
struct TYPE_5__ {TYPE_1__* sc; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_4__ {int /*<<< orphan*/  adp; } ;

/* Variables and functions */
 int /*<<< orphan*/  vidd_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gfb_clear(scr_stat *scp, int c, int attr)
{
	vidd_clear(scp->sc->adp);
}