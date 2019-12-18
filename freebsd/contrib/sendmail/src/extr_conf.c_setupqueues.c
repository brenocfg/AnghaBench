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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MaxRunnersPerQueue ; 
 int /*<<< orphan*/  makequeue (char*,int) ; 
 int /*<<< orphan*/  sm_strlcpy (char*,char*,int) ; 

__attribute__((used)) static void
setupqueues()
{
	char buf[100];

	MaxRunnersPerQueue = 1;
	(void) sm_strlcpy(buf, "mqueue, P=/var/spool/mqueue", sizeof(buf));
	makequeue(buf, false);
}