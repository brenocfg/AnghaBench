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
struct in_addr {int dummy; } ;
struct TYPE_2__ {struct in_addr frag_addr; } ;
struct alias_link {TYPE_1__ data; } ;

/* Variables and functions */

void
SetFragmentAddr(struct alias_link *lnk, struct in_addr src_addr)
{
	lnk->data.frag_addr = src_addr;
}