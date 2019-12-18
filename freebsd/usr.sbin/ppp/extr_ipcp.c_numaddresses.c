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
numaddresses(struct in_addr mask)
{
  u_int32_t bit, haddr;
  int n;

  haddr = ntohl(mask.s_addr);
  bit = 1;
  n = 1;

  do {
    if (!(haddr & bit))
      n <<= 1;
  } while (bit <<= 1);

  return n;
}