#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netadrtype_t ;
struct TYPE_5__ {void* port; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ netadr_t ;
typedef  int /*<<< orphan*/  base ;

/* Variables and functions */
 void* BigShort (short) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int MAX_STRING_CHARS ; 
 int /*<<< orphan*/  NA_BAD ; 
 int /*<<< orphan*/  NA_LOOPBACK ; 
 short PORT_SERVER ; 
 int Q_CountChar (char*,char) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char const*,int) ; 
 int /*<<< orphan*/  Sys_StringToAdr (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ atoi (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int NET_StringToAdr( const char *s, netadr_t *a, netadrtype_t family )
{
	char	base[MAX_STRING_CHARS], *search;
	char	*port = NULL;

	if (!strcmp (s, "localhost")) {
		Com_Memset (a, 0, sizeof(*a));
		a->type = NA_LOOPBACK;
// as NA_LOOPBACK doesn't require ports report port was given.
		return 1;
	}

	Q_strncpyz( base, s, sizeof( base ) );
	
	if(*base == '[' || Q_CountChar(base, ':') > 1)
	{
		// This is an ipv6 address, handle it specially.
		search = strchr(base, ']');
		if(search)
		{
			*search = '\0';
			search++;

			if(*search == ':')
				port = search + 1;
		}
		
		if(*base == '[')
			search = base + 1;
		else
			search = base;
	}
	else
	{
		// look for a port number
		port = strchr( base, ':' );
		
		if ( port ) {
			*port = '\0';
			port++;
		}
		
		search = base;
	}

	if(!Sys_StringToAdr(search, a, family))
	{
		a->type = NA_BAD;
		return 0;
	}

	if(port)
	{
		a->port = BigShort((short) atoi(port));
		return 1;
	}
	else
	{
		a->port = BigShort(PORT_SERVER);
		return 2;
	}
}