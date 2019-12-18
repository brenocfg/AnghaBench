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
typedef  int /*<<< orphan*/  u_int32_t ;
struct lqrdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

void
lqr_ChangeOrder(struct lqrdata *src, struct lqrdata *dst)
{
  u_int32_t *sp, *dp;
  unsigned n;

  sp = (u_int32_t *) src;
  dp = (u_int32_t *) dst;
  for (n = 0; n < sizeof(struct lqrdata) / sizeof(u_int32_t); n++, sp++, dp++)
    *dp = ntohl(*sp);
}