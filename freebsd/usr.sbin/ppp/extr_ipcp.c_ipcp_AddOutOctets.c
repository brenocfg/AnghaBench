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
struct ipcp {int /*<<< orphan*/  throughput; } ;

/* Variables and functions */
 int /*<<< orphan*/  throughput_addout (int /*<<< orphan*/ *,int) ; 

void
ipcp_AddOutOctets(struct ipcp *ipcp, int n)
{
  throughput_addout(&ipcp->throughput, n);
}