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
 int AF_INET ; 
 int AF_INET6 ; 

const char *familyname(int family)
{
	if (family == AF_INET)
		return "inet";
#ifdef USE_INET6
	if (family == AF_INET6)
		return "inet6";
#endif
	return "unknown";
}