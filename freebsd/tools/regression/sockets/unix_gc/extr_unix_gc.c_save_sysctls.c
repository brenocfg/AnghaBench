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
 int getinflight () ; 
 int getopenfiles () ; 

__attribute__((used)) static void
save_sysctls(int *before_inflight, int *before_openfiles)
{

	*before_inflight = getinflight();
	*before_openfiles = getopenfiles();
}