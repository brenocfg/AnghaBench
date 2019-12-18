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
 int /*<<< orphan*/  code ; 
 int /*<<< orphan*/  epsv6 ; 
 scalar_t__ epsv6bad ; 
 int /*<<< orphan*/  togglevar (int,char**,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ verbose ; 

void
setepsv6(int argc, char *argv[])
{
	code = togglevar(argc, argv, &epsv6,
	    verbose ? "EPSV/EPRT on IPv6" : NULL);
	epsv6bad = 0;
}