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
struct mbuf {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_CHECK (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_MBUF ; 
 int /*<<< orphan*/  netinet_icmp_reply ; 

__attribute__((used)) static void
test_netinet_icmp_reply(struct mbuf *mrecv, struct label *mrecvlabel,
    struct mbuf *msend, struct label *msendlabel)
{

	LABEL_CHECK(mrecvlabel, MAGIC_MBUF);
	LABEL_CHECK(msendlabel, MAGIC_MBUF);
	COUNTER_INC(netinet_icmp_reply);
}