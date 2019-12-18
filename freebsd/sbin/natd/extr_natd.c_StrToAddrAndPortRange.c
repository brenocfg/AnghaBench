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
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  port_range ;

/* Variables and functions */
 int /*<<< orphan*/  StrToAddr (char*,struct in_addr*) ; 
 int StrToPortRange (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
StrToAddrAndPortRange (char* str, struct in_addr* addr, char* proto, port_range *portRange)
{
	char*	ptr;

	ptr = strchr (str, ':');
	if (!ptr)
		errx (1, "%s is missing port number", str);

	*ptr = '\0';
	++ptr;

	StrToAddr (str, addr);
	return StrToPortRange (ptr, proto, portRange);
}