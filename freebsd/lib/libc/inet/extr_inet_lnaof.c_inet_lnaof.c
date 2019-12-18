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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int /*<<< orphan*/  in_addr_t ;
typedef  int /*<<< orphan*/  i ;

/* Variables and functions */
 scalar_t__ IN_CLASSA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_CLASSA_HOST ; 
 scalar_t__ IN_CLASSB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_CLASSB_HOST ; 
 int /*<<< orphan*/  IN_CLASSC_HOST ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

in_addr_t
inet_lnaof(struct in_addr in)
{
	in_addr_t i = ntohl(in.s_addr);

	if (IN_CLASSA(i))
		return ((i)&IN_CLASSA_HOST);
	else if (IN_CLASSB(i))
		return ((i)&IN_CLASSB_HOST);
	else
		return ((i)&IN_CLASSC_HOST);
}