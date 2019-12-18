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
typedef  scalar_t__ u_short ;
struct lcp {scalar_t__ his_acfcomp; } ;

/* Variables and functions */
 scalar_t__ PROTO_LCP ; 

int
acf_WrapperOctets(struct lcp *lcp, u_short proto)
{
  return (proto == PROTO_LCP || lcp->his_acfcomp == 0) ? 2 : 0;
}