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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addrbuf ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,char*) ; 
 scalar_t__ NA_IP ; 
 scalar_t__ NA_IP6 ; 
 int NET_ADDRSTRMAXLEN ; 
 int /*<<< orphan*/  Sys_SockaddrToString (char*,int,struct sockaddr*) ; 
 TYPE_1__* localIP ; 
 int numIP ; 

void Sys_ShowIP(void) {
	int i;
	char addrbuf[NET_ADDRSTRMAXLEN];

	for(i = 0; i < numIP; i++)
	{
		Sys_SockaddrToString(addrbuf, sizeof(addrbuf), (struct sockaddr *) &localIP[i].addr);

		if(localIP[i].type == NA_IP)
			Com_Printf( "IP: %s\n", addrbuf);
		else if(localIP[i].type == NA_IP6)
			Com_Printf( "IP6: %s\n", addrbuf);
	}
}