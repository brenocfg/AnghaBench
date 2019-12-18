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
 int FWD_PERMIT_ANY_PORT ; 
 int a2port (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int
permitopen_port(const char *p)
{
	int port;

	if (strcmp(p, "*") == 0)
		return FWD_PERMIT_ANY_PORT;
	if ((port = a2port(p)) > 0)
		return port;
	return -1;
}