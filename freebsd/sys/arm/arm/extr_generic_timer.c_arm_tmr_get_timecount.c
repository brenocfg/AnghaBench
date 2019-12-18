#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timecounter {int dummy; } ;
struct TYPE_2__ {int (* get_cntxct ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  physical; } ;

/* Variables and functions */
 TYPE_1__* arm_tmr_sc ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
arm_tmr_get_timecount(struct timecounter *tc)
{

	return (arm_tmr_sc->get_cntxct(arm_tmr_sc->physical));
}