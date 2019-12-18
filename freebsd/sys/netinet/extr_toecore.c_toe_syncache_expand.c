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
struct tcpopt {int dummy; } ;
struct tcphdr {int dummy; } ;
struct socket {int dummy; } ;
struct in_conninfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 int syncache_expand (struct in_conninfo*,struct tcpopt*,struct tcphdr*,struct socket**,int /*<<< orphan*/ *) ; 

int
toe_syncache_expand(struct in_conninfo *inc, struct tcpopt *to,
    struct tcphdr *th, struct socket **lsop)
{

	NET_EPOCH_ASSERT();

	return (syncache_expand(inc, to, th, lsop, NULL));
}