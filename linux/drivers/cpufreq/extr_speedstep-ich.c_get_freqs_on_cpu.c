#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct get_freqs {TYPE_2__* policy; int /*<<< orphan*/  ret; } ;
struct TYPE_6__ {int /*<<< orphan*/  frequency; } ;
struct TYPE_4__ {int /*<<< orphan*/  transition_latency; } ;
struct TYPE_5__ {TYPE_1__ cpuinfo; } ;

/* Variables and functions */
 size_t SPEEDSTEP_HIGH ; 
 size_t SPEEDSTEP_LOW ; 
 TYPE_3__* speedstep_freqs ; 
 int /*<<< orphan*/  speedstep_get_freqs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  speedstep_processor ; 
 int /*<<< orphan*/  speedstep_set_state ; 

__attribute__((used)) static void get_freqs_on_cpu(void *_get_freqs)
{
	struct get_freqs *get_freqs = _get_freqs;

	get_freqs->ret =
		speedstep_get_freqs(speedstep_processor,
			    &speedstep_freqs[SPEEDSTEP_LOW].frequency,
			    &speedstep_freqs[SPEEDSTEP_HIGH].frequency,
			    &get_freqs->policy->cpuinfo.transition_latency,
			    &speedstep_set_state);
}