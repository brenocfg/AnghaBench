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
struct TYPE_3__ {scalar_t__ state; } ;
typedef  TYPE_1__ pthread_once_t ;

/* Variables and functions */
 scalar_t__ PTHREAD_DONE_INIT ; 

__attribute__((used)) static int
_libc_once(pthread_once_t *once_control, void (*init_routine)(void))
{

	if (once_control->state == PTHREAD_DONE_INIT)
		return (0);
	init_routine();
	once_control->state = PTHREAD_DONE_INIT;
	return (0);
}