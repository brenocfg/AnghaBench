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
struct ncprange {int dummy; } ;

/* Variables and functions */
#define  T_DNS0 131 
#define  T_DNS1 130 
#define  T_HISADDR 129 
#define  T_MYADDR 128 
 char const* ncprange_ntoa (struct ncprange*) ; 

__attribute__((used)) static const char *
addrstr(struct ncprange *addr, unsigned type)
{
  switch (type) {
    case T_MYADDR:
      return "MYADDR";
    case T_HISADDR:
      return "HISADDR";
    case T_DNS0:
      return "DNS0";
    case T_DNS1:
      return "DNS1";
  }
  return ncprange_ntoa(addr);
}