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
 int P_OSREL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __FreeBSD_version ; 
 int /*<<< orphan*/  gone_panic (int,int,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
_gone_in(int major, const char *msg)
{

	gone_panic(major, P_OSREL_MAJOR(__FreeBSD_version), msg);
	if (P_OSREL_MAJOR(__FreeBSD_version) >= major)
		printf("Obsolete code will removed soon: %s\n", msg);
	else
		printf("Deprecated code (to be removed in FreeBSD %d): %s\n",
		    major, msg);
}