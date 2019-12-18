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
struct icmphdr {int icmp_type; } ;

/* Variables and functions */
 int ICMP_MAXTYPE ; 
 int TT ; 

__attribute__((used)) static int
is_icmp_query(struct icmphdr *icmp)
{
	int type = icmp->icmp_type;

	return (type <= ICMP_MAXTYPE && (TT & (1<<type)) );
}