#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  port; } ;
struct TYPE_4__ {int time; int start; int /*<<< orphan*/  info; TYPE_2__ adr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_SetServerInfoByAddress (TYPE_2__,int /*<<< orphan*/ ,int) ; 
 int Cvar_VariableIntegerValue (char*) ; 
 int MAX_PINGREQUESTS ; 
 char* NET_AdrToStringwPort (TYPE_2__) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char const*,int) ; 
 int Sys_Milliseconds () ; 
 TYPE_1__* cl_pinglist ; 

void CL_GetPing( int n, char *buf, int buflen, int *pingtime )
{
	const char	*str;
	int		time;
	int		maxPing;

	if (n < 0 || n >= MAX_PINGREQUESTS || !cl_pinglist[n].adr.port)
	{
		// empty or invalid slot
		buf[0]    = '\0';
		*pingtime = 0;
		return;
	}

	str = NET_AdrToStringwPort( cl_pinglist[n].adr );
	Q_strncpyz( buf, str, buflen );

	time = cl_pinglist[n].time;
	if (!time)
	{
		// check for timeout
		time = Sys_Milliseconds() - cl_pinglist[n].start;
		maxPing = Cvar_VariableIntegerValue( "cl_maxPing" );
		if( maxPing < 100 ) {
			maxPing = 100;
		}
		if (time < maxPing)
		{
			// not timed out yet
			time = 0;
		}
	}

	CL_SetServerInfoByAddress(cl_pinglist[n].adr, cl_pinglist[n].info, cl_pinglist[n].time);

	*pingtime = time;
}