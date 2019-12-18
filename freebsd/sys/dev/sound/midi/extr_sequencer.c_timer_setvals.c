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
struct seq_softc {int tempo; int timerbase; } ;

/* Variables and functions */

__attribute__((used)) static void
timer_setvals(struct seq_softc *t, int tempo, int timerbase)
{
	t->tempo = tempo;
	t->timerbase = timerbase;
}