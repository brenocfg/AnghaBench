#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ isexception; int /*<<< orphan*/  subnet; int /*<<< orphan*/  ip; } ;
typedef  TYPE_1__ serverBan_t ;
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  netadr_t ;

/* Variables and functions */
 scalar_t__ NET_CompareBaseAdrMask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 TYPE_1__* serverBans ; 
 int serverBansCount ; 

__attribute__((used)) static qboolean SV_IsBanned(netadr_t *from, qboolean isexception)
{
	int index;
	serverBan_t *curban;
	
	if(!isexception)
	{
		// If this is a query for a ban, first check whether the client is excepted
		if(SV_IsBanned(from, qtrue))
			return qfalse;
	}
	
	for(index = 0; index < serverBansCount; index++)
	{
		curban = &serverBans[index];
		
		if(curban->isexception == isexception)
		{
			if(NET_CompareBaseAdrMask(curban->ip, *from, curban->subnet))
				return qtrue;
		}
	}
	
	return qfalse;
}