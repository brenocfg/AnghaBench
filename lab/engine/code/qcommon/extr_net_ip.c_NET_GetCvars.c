#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  void* qboolean ;
struct TYPE_24__ {int modified; } ;
struct TYPE_23__ {int modified; } ;
struct TYPE_22__ {int modified; } ;
struct TYPE_21__ {int modified; } ;
struct TYPE_20__ {int modified; } ;
struct TYPE_19__ {int modified; } ;
struct TYPE_18__ {int modified; } ;
struct TYPE_17__ {int modified; } ;
struct TYPE_16__ {int modified; } ;
struct TYPE_15__ {int modified; } ;
struct TYPE_14__ {int modified; } ;
struct TYPE_13__ {int modified; } ;

/* Variables and functions */
 int CVAR_ARCHIVE ; 
 int CVAR_LATCH ; 
 int CVAR_TEMP ; 
 void* Cvar_Get (char*,char*,int) ; 
 char* NET_MULTICAST_IP6 ; 
 int /*<<< orphan*/  PORT_SERVER ; 
 void* net_dropsim ; 
 TYPE_12__* net_enabled ; 
 TYPE_11__* net_ip ; 
 TYPE_10__* net_ip6 ; 
 TYPE_9__* net_mcast6addr ; 
 TYPE_8__* net_mcast6iface ; 
 TYPE_7__* net_port ; 
 TYPE_6__* net_port6 ; 
 TYPE_5__* net_socksEnabled ; 
 TYPE_4__* net_socksPassword ; 
 TYPE_3__* net_socksPort ; 
 TYPE_2__* net_socksServer ; 
 TYPE_1__* net_socksUsername ; 
 void* qfalse ; 
 void* qtrue ; 
 char* va (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static qboolean NET_GetCvars( void ) {
	int modified;

#ifdef DEDICATED
	// I want server owners to explicitly turn on ipv6 support.
	net_enabled = Cvar_Get( "net_enabled", "1", CVAR_LATCH | CVAR_ARCHIVE );
#else
	/* End users have it enabled so they can connect to ipv6-only hosts, but ipv4 will be
	 * used if available due to ping */
	net_enabled = Cvar_Get( "net_enabled", "3", CVAR_LATCH | CVAR_ARCHIVE );
#endif
	modified = net_enabled->modified;
	net_enabled->modified = qfalse;

	net_ip = Cvar_Get( "net_ip", "0.0.0.0", CVAR_LATCH );
	modified += net_ip->modified;
	net_ip->modified = qfalse;
	
	net_ip6 = Cvar_Get( "net_ip6", "::", CVAR_LATCH );
	modified += net_ip6->modified;
	net_ip6->modified = qfalse;
	
	net_port = Cvar_Get( "net_port", va( "%i", PORT_SERVER ), CVAR_LATCH );
	modified += net_port->modified;
	net_port->modified = qfalse;
	
	net_port6 = Cvar_Get( "net_port6", va( "%i", PORT_SERVER ), CVAR_LATCH );
	modified += net_port6->modified;
	net_port6->modified = qfalse;

	// Some cvars for configuring multicast options which facilitates scanning for servers on local subnets.
	net_mcast6addr = Cvar_Get( "net_mcast6addr", NET_MULTICAST_IP6, CVAR_LATCH | CVAR_ARCHIVE );
	modified += net_mcast6addr->modified;
	net_mcast6addr->modified = qfalse;

#ifdef _WIN32
	net_mcast6iface = Cvar_Get( "net_mcast6iface", "0", CVAR_LATCH | CVAR_ARCHIVE );
#else
	net_mcast6iface = Cvar_Get( "net_mcast6iface", "", CVAR_LATCH | CVAR_ARCHIVE );
#endif
	modified += net_mcast6iface->modified;
	net_mcast6iface->modified = qfalse;

	net_socksEnabled = Cvar_Get( "net_socksEnabled", "0", CVAR_LATCH | CVAR_ARCHIVE );
	modified += net_socksEnabled->modified;
	net_socksEnabled->modified = qfalse;

	net_socksServer = Cvar_Get( "net_socksServer", "", CVAR_LATCH | CVAR_ARCHIVE );
	modified += net_socksServer->modified;
	net_socksServer->modified = qfalse;

	net_socksPort = Cvar_Get( "net_socksPort", "1080", CVAR_LATCH | CVAR_ARCHIVE );
	modified += net_socksPort->modified;
	net_socksPort->modified = qfalse;

	net_socksUsername = Cvar_Get( "net_socksUsername", "", CVAR_LATCH | CVAR_ARCHIVE );
	modified += net_socksUsername->modified;
	net_socksUsername->modified = qfalse;

	net_socksPassword = Cvar_Get( "net_socksPassword", "", CVAR_LATCH | CVAR_ARCHIVE );
	modified += net_socksPassword->modified;
	net_socksPassword->modified = qfalse;

	net_dropsim = Cvar_Get("net_dropsim", "", CVAR_TEMP);

	return modified ? qtrue : qfalse;
}