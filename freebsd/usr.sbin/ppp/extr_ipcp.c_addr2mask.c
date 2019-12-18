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
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 scalar_t__ IN_CLASSA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_CLASSA_NET ; 
 scalar_t__ IN_CLASSB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_CLASSB_NET ; 
 int /*<<< orphan*/  IN_CLASSC_NET ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

struct in_addr
addr2mask(struct in_addr addr)
{
  u_int32_t haddr = ntohl(addr.s_addr);

  haddr = IN_CLASSA(haddr) ? IN_CLASSA_NET :
          IN_CLASSB(haddr) ? IN_CLASSB_NET :
          IN_CLASSC_NET;
  addr.s_addr = htonl(haddr);

  return addr;
}