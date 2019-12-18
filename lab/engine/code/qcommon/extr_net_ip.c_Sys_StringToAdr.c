#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sadr ;
typedef  int /*<<< orphan*/  sa_family_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int netadrtype_t ;
typedef  int /*<<< orphan*/  netadr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
#define  NA_IP 129 
#define  NA_IP6 128 
 int /*<<< orphan*/  SockadrToNetadr (struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Sys_StringToSockaddr (char const*,struct sockaddr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean Sys_StringToAdr( const char *s, netadr_t *a, netadrtype_t family ) {
	struct sockaddr_storage sadr;
	sa_family_t fam;
	
	switch(family)
	{
		case NA_IP:
			fam = AF_INET;
		break;
		case NA_IP6:
			fam = AF_INET6;
		break;
		default:
			fam = AF_UNSPEC;
		break;
	}
	if( !Sys_StringToSockaddr(s, (struct sockaddr *) &sadr, sizeof(sadr), fam ) ) {
		return qfalse;
	}
	
	SockadrToNetadr( (struct sockaddr *) &sadr, a );
	return qtrue;
}