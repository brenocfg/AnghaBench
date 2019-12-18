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
typedef  int /*<<< orphan*/  u_short ;
struct sockaddr_s {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct hostent {scalar_t__* h_addr_list; } ;
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ DEFAULTnet_hostport ; 
 int /*<<< orphan*/  INADDR_BROADCAST ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int MAXHOSTNAMELEN ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  WINS_AddrToString (struct sockaddr_s*) ; 
 int /*<<< orphan*/  WINS_GetSocketAddr (int,struct sockaddr_s*) ; 
 int WINS_OpenSocket (int /*<<< orphan*/ ) ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WinError (char*) ; 
 int /*<<< orphan*/  WinPrint (char*) ; 
 int /*<<< orphan*/  broadcastaddr ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int myAddr ; 
 int /*<<< orphan*/  my_tcpip_address ; 
 int net_controlsocket ; 
 scalar_t__ net_hostport ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  winsockdata ; 

int WINS_Init( void ){
	int i;
	struct hostent *local;
	char buff[MAXHOSTNAMELEN];
	struct sockaddr_s addr;
	char    *p;
/*
   linux doesn't have anything to initialize for the net
   "Windows .. built for the internet .. the internet .. built with unix"
 */
#if 0
	int r;
	WORD wVersionRequested;

	wVersionRequested = MAKEWORD( 2, 2 );

	r = WSAStartup( wVersionRequested, &winsockdata );

	if ( r ) {
		WinPrint( "Winsock initialization failed.\n" );
		return -1;
	}
#endif
	/*
	   i = COM_CheckParm ("-udpport");
	   if (i == 0)*/
	net_hostport = DEFAULTnet_hostport;
	/*
	   else if (i < com_argc-1)
	    net_hostport = Q_atoi (com_argv[i+1]);
	   else
	    Sys_Error ("WINS_Init: you must specify a number after -udpport");
	 */

	// determine my name & address
	gethostname( buff, MAXHOSTNAMELEN );
	local = gethostbyname( buff );

	// When hostname can not be resolved, return gracefully
	if ( local == 0 ) {
		WinError( "WINS_Init: Unable to resolve hostname\n" );
		return 0;
	}

	myAddr = *(int *)local->h_addr_list[0];

	// if the quake hostname isn't set, set it to the machine name
//	if (Q_strcmp(hostname.string, "UNNAMED") == 0)
	{
		// see if it's a text IP address (well, close enough)
		for ( p = buff; *p; p++ )
			if ( ( *p < '0' || *p > '9' ) && *p != '.' ) {
				break;
			}

		// if it is a real name, strip off the domain; we only want the host
		if ( *p ) {
			for ( i = 0; i < 15; i++ )
				if ( buff[i] == '.' ) {
					break;
				}
			buff[i] = 0;
		}
//		Cvar_Set ("hostname", buff);
	}

	//++timo WTF is that net_controlsocket? it's sole purpose is to retrieve the local IP?
	if ( ( net_controlsocket = WINS_OpenSocket( 0 ) ) == SOCKET_ERROR ) {
		WinError( "WINS_Init: Unable to open control socket\n" );
	}

	( (struct sockaddr_in *)&broadcastaddr )->sin_family = AF_INET;
	( (struct sockaddr_in *)&broadcastaddr )->sin_addr.s_addr = INADDR_BROADCAST;
	( (struct sockaddr_in *)&broadcastaddr )->sin_port = htons( (u_short)net_hostport );

	WINS_GetSocketAddr( net_controlsocket, &addr );
	strcpy( my_tcpip_address,  WINS_AddrToString( &addr ) );
	p = strrchr( my_tcpip_address, ':' );
	if ( p ) {
		*p = 0;
	}
	WinPrint( "Winsock Initialized\n" );

	return net_controlsocket;
}