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
 int /*<<< orphan*/  MON_RES ; 
 int /*<<< orphan*/  mon_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_limited_refcnt ; 

__attribute__((used)) static void
inc_res_limited(void)
{
	if (!res_limited_refcnt)
		mon_start(MON_RES);
	res_limited_refcnt++;
}