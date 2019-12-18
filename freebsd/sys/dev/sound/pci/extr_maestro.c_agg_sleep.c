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
struct agg_info {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWAIT ; 
 int hz ; 
 int /*<<< orphan*/  msleep (struct agg_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
agg_sleep(struct agg_info *sc, const char *wmesg, int msec)
{
	int timo;

	timo = msec * hz / 1000;
	if (timo == 0)
		timo = 1;
	msleep(sc, &sc->lock, PWAIT, wmesg, timo);
}