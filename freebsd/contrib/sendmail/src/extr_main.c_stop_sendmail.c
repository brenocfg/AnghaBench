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
 int /*<<< orphan*/  EX_OK ; 
 int /*<<< orphan*/  RealUid ; 
 int /*<<< orphan*/  endpwent () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setuid (int /*<<< orphan*/ ) ; 

void
stop_sendmail()
{
	/* reset uid for process accounting */
	endpwent();
	(void) setuid(RealUid);
	exit(EX_OK);
}