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
struct TYPE_4__ {int /*<<< orphan*/  sival_ptr; } ;
struct TYPE_5__ {int si_code; int si_timerid; int si_mqd; TYPE_1__ si_value; } ;
typedef  TYPE_2__ siginfo_t ;
typedef  int sigev_id_t ;

/* Variables and functions */
#define  SI_ASYNCIO 130 
#define  SI_MESGQ 129 
#define  SI_TIMER 128 

__attribute__((used)) static sigev_id_t
sigev_get_id(siginfo_t *si)
{
	switch(si->si_code) {
	case SI_TIMER:
		return (si->si_timerid);
	case SI_MESGQ:
		return (si->si_mqd);
	case SI_ASYNCIO:
		return (sigev_id_t)si->si_value.sival_ptr;
	}
	return (-1);
}