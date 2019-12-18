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
typedef  int /*<<< orphan*/  td_thread_t ;

/* Variables and functions */
 int TD_ERR_OK ; 

__attribute__((used)) static int
iterateThreads1(td_thread_t *thread, void *arg)
{

	return TD_ERR_OK;
}