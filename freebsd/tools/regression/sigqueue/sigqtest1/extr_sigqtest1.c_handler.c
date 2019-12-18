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
struct TYPE_4__ {scalar_t__ sival_int; } ;
struct TYPE_5__ {scalar_t__ si_code; TYPE_1__ si_value; } ;
typedef  TYPE_2__ siginfo_t ;

/* Variables and functions */
 scalar_t__ SI_QUEUE ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ received ; 

void
handler(int sig, siginfo_t *si, void *ctx)
{
	if (si->si_code != SI_QUEUE)
		errx(1, "si_code != SI_QUEUE");
	if (si->si_value.sival_int != received)
		errx(1, "signal is out of order");
	received++;
}