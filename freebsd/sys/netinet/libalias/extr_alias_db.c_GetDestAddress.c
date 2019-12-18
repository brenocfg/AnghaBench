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
struct in_addr {int dummy; } ;
struct alias_link {struct in_addr dst_addr; } ;

/* Variables and functions */

struct in_addr
GetDestAddress(struct alias_link *lnk)
{
	return (lnk->dst_addr);
}