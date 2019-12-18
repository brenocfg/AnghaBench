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
struct sctphdr {int dummy; } ;
struct sctp_nets {scalar_t__ cwnd; int mtu; } ;
struct sctp_association {scalar_t__ max_cwnd; } ;

/* Variables and functions */

__attribute__((used)) static void
sctp_enforce_cwnd_limit(struct sctp_association *assoc, struct sctp_nets *net)
{
	if ((assoc->max_cwnd > 0) &&
	    (net->cwnd > assoc->max_cwnd) &&
	    (net->cwnd > (net->mtu - sizeof(struct sctphdr)))) {
		net->cwnd = assoc->max_cwnd;
		if (net->cwnd < (net->mtu - sizeof(struct sctphdr))) {
			net->cwnd = net->mtu - sizeof(struct sctphdr);
		}
	}
}