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
typedef  int u_int ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int) ; 

__attribute__((used)) static int
IpMask(int nbits, struct in_addr *mask)
{
	int i;
	u_int imask;

	if (nbits < 0 || nbits > 32)
		return (-1);

	imask = 0;
	for (i = 0; i < nbits; i++)
		imask = (imask >> 1) + 0x80000000;
	mask->s_addr = htonl(imask);

	return (0);
}