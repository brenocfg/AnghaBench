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
typedef  int u_int32_t ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mask42bits(struct in_addr mask)
{
  u_int32_t msk = ntohl(mask.s_addr);
  u_int32_t tst;
  int ret;

  for (ret = 32, tst = 1; tst; ret--, tst <<= 1)
    if (msk & tst)
      break;

  for (tst <<= 1; tst; tst <<= 1)
    if (!(msk & tst))
      break;

  return tst ? -1 : ret;
}