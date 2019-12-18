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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int join_common (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 

int
_thr_join(pthread_t pthread, void **thread_return)
{
	return (join_common(pthread, thread_return, NULL));
}