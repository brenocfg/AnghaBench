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
typedef  size_t rpcvers_t ;
typedef  scalar_t__ bool_t ;
struct TYPE_2__ {int /*<<< orphan*/  unsetinfo; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 size_t RPCBVERS_STAT ; 
 TYPE_1__* inf ; 

void
rpcbs_unset(rpcvers_t rtype, bool_t success)
{
	if ((rtype >= RPCBVERS_STAT) || (success == FALSE))
		return;
	inf[rtype].unsetinfo++;
	return;
}