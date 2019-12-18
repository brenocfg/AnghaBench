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
struct ipv6cp {struct mqueue* Queue; } ;

/* Variables and functions */
 int IPV6CP_QUEUES (struct ipv6cp*) ; 

size_t
ipv6cp_QueueLen(struct ipv6cp *ipv6cp)
{
  struct mqueue *q;
  size_t result;

  result = 0;
  for (q = ipv6cp->Queue; q < ipv6cp->Queue + IPV6CP_QUEUES(ipv6cp); q++)
    result += q->len;

  return result;
}