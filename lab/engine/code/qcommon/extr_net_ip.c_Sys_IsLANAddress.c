#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {scalar_t__ type; int* ip; int* ip6; } ;
typedef  TYPE_2__ netadr_t ;
typedef  int byte ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  netmask; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ NA_IP ; 
 scalar_t__ NA_IP6 ; 
 scalar_t__ NA_LOOPBACK ; 
 TYPE_3__* localIP ; 
 int numIP ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean Sys_IsLANAddress( netadr_t adr ) {
	int		index, run, addrsize;
	qboolean differed;
	byte *compareadr, *comparemask, *compareip;

	if( adr.type == NA_LOOPBACK ) {
		return qtrue;
	}

	if( adr.type == NA_IP )
	{
		// RFC1918:
		// 10.0.0.0        -   10.255.255.255  (10/8 prefix)
		// 172.16.0.0      -   172.31.255.255  (172.16/12 prefix)
		// 192.168.0.0     -   192.168.255.255 (192.168/16 prefix)
		if(adr.ip[0] == 10)
			return qtrue;
		if(adr.ip[0] == 172 && (adr.ip[1]&0xf0) == 16)
			return qtrue;
		if(adr.ip[0] == 192 && adr.ip[1] == 168)
			return qtrue;

		if(adr.ip[0] == 127)
			return qtrue;
	}
	else if(adr.type == NA_IP6)
	{
		if(adr.ip6[0] == 0xfe && (adr.ip6[1] & 0xc0) == 0x80)
			return qtrue;
		if((adr.ip6[0] & 0xfe) == 0xfc)
			return qtrue;
	}
	
	// Now compare against the networks this computer is member of.
	for(index = 0; index < numIP; index++)
	{
		if(localIP[index].type == adr.type)
		{
			if(adr.type == NA_IP)
			{
				compareip = (byte *) &((struct sockaddr_in *) &localIP[index].addr)->sin_addr.s_addr;
				comparemask = (byte *) &((struct sockaddr_in *) &localIP[index].netmask)->sin_addr.s_addr;
				compareadr = adr.ip;
				
				addrsize = sizeof(adr.ip);
			}
			else
			{
				// TODO? should we check the scope_id here?

				compareip = (byte *) &((struct sockaddr_in6 *) &localIP[index].addr)->sin6_addr;
				comparemask = (byte *) &((struct sockaddr_in6 *) &localIP[index].netmask)->sin6_addr;
				compareadr = adr.ip6;
				
				addrsize = sizeof(adr.ip6);
			}

			differed = qfalse;
			for(run = 0; run < addrsize; run++)
			{
				if((compareip[run] & comparemask[run]) != (compareadr[run] & comparemask[run]))
				{
					differed = qtrue;
					break;
				}
			}
			
			if(!differed)
				return qtrue;

		}
	}
	
	return qfalse;
}