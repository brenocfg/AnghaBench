#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {scalar_t__ unsentFragments; } ;
typedef  TYPE_1__ netchan_t ;

/* Variables and functions */
 int /*<<< orphan*/  Netchan_TransmitNextFragment (TYPE_1__*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean CL_Netchan_TransmitNextFragment(netchan_t *chan)
{
	if(chan->unsentFragments)
	{
		Netchan_TransmitNextFragment(chan);
		return qtrue;
	}
	
	return qfalse;
}