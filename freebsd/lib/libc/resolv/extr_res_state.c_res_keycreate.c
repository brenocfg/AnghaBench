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

/* Variables and functions */
 int /*<<< orphan*/  free_res ; 
 int /*<<< orphan*/  res_key ; 
 int res_thr_keycreated ; 
 scalar_t__ thr_keycreate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
res_keycreate(void)
{
	res_thr_keycreated = thr_keycreate(&res_key, free_res) == 0;
}