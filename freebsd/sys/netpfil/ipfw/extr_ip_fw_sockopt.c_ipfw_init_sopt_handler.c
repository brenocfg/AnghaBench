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
 int /*<<< orphan*/  CTL3_LOCK_INIT () ; 
 int /*<<< orphan*/  IPFW_ADD_SOPT_HANDLER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scodes ; 

void
ipfw_init_sopt_handler()
{

	CTL3_LOCK_INIT();
	IPFW_ADD_SOPT_HANDLER(1, scodes);
}