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
typedef  int /*<<< orphan*/  u_char ;
struct udphdr {int /*<<< orphan*/  uh_dport; int /*<<< orphan*/  uh_sport; } ;

/* Variables and functions */
 scalar_t__ fixedPort ; 
 scalar_t__ ident ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ port ; 

int
udplite_check(const u_char *data, int seq)
{
	struct udphdr *const udp = (struct udphdr *) data;

	return (ntohs(udp->uh_sport) == ident + (fixedPort ? seq : 0) &&
	    ntohs(udp->uh_dport) == port + (fixedPort ? 0 : seq));
}