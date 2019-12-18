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
struct mqueue {scalar_t__ len; } ;
struct ipcp {struct mqueue* Queue; } ;

/* Variables and functions */
 int IPCP_QUEUES (struct ipcp*) ; 

size_t
ipcp_QueueLen(struct ipcp *ipcp)
{
  struct mqueue *q;
  size_t result;

  result = 0;
  for (q = ipcp->Queue; q < ipcp->Queue + IPCP_QUEUES(ipcp); q++)
    result += q->len;

  return result;
}