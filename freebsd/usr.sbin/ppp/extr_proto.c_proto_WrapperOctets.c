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
typedef  int u_short ;
struct lcp {scalar_t__ his_protocomp; } ;

/* Variables and functions */

int
proto_WrapperOctets(struct lcp *lcp, u_short proto)
{
  return (lcp->his_protocomp && !(proto & 0xff00)) ? 1 : 2;
}