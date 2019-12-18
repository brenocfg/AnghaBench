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
 int AF_LINK ; 
 int AF_UNSPEC ; 
 scalar_t__ feature_present (char*) ; 

__attribute__((used)) static int
get_socket_domain(void)
{
	int sdom;

	sdom = AF_UNSPEC;
#ifdef WITH_INET6
	if (sdom == AF_UNSPEC && feature_present("inet6"))
		sdom = AF_INET6;
#endif
#ifdef WITH_INET
	if (sdom == AF_UNSPEC && feature_present("inet"))
		sdom = AF_INET;
#endif
	if (sdom == AF_UNSPEC)
		sdom = AF_LINK;

	return (sdom);
}