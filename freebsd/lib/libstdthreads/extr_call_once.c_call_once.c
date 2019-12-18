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
typedef  int /*<<< orphan*/  pthread_once_t ;
typedef  int /*<<< orphan*/  once_flag ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_once (int /*<<< orphan*/ *,void (*) ()) ; 

void
call_once(once_flag *flag, void (*func)(void))
{

	(void)pthread_once((pthread_once_t *)flag, func);
}