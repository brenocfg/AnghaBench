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
typedef  scalar_t__ in_addr_t ;

/* Variables and functions */
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

int
prison_qcmp_v4(const void *ip1, const void *ip2)
{
	in_addr_t iaa, iab;

	/*
	 * We need to compare in HBO here to get the list sorted as expected
	 * by the result of the code.  Sorting NBO addresses gives you
	 * interesting results.  If you do not understand, do not try.
	 */
	iaa = ntohl(((const struct in_addr *)ip1)->s_addr);
	iab = ntohl(((const struct in_addr *)ip2)->s_addr);

	/*
	 * Do not simply return the difference of the two numbers, the int is
	 * not wide enough.
	 */
	if (iaa > iab)
		return (1);
	else if (iaa < iab)
		return (-1);
	else
		return (0);
}