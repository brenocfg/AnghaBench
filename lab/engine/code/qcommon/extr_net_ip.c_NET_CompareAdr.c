#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ port; } ;
typedef  TYPE_1__ netadr_t ;

/* Variables and functions */
 scalar_t__ NA_IP ; 
 scalar_t__ NA_IP6 ; 
 int /*<<< orphan*/  NET_CompareBaseAdr (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean	NET_CompareAdr (netadr_t a, netadr_t b)
{
	if(!NET_CompareBaseAdr(a, b))
		return qfalse;
	
	if (a.type == NA_IP || a.type == NA_IP6)
	{
		if (a.port == b.port)
			return qtrue;
	}
	else
		return qtrue;
		
	return qfalse;
}