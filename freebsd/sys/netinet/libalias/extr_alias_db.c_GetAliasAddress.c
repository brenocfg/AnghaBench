#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct in_addr {scalar_t__ s_addr; } ;
struct alias_link {struct in_addr alias_addr; TYPE_1__* la; } ;
struct TYPE_2__ {struct in_addr aliasAddress; } ;

/* Variables and functions */
 scalar_t__ INADDR_ANY ; 

struct in_addr
GetAliasAddress(struct alias_link *lnk)
{
	if (lnk->alias_addr.s_addr == INADDR_ANY)
		return (lnk->la->aliasAddress);
	else
		return (lnk->alias_addr);
}