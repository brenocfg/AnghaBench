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
struct sockaddr_s {int /*<<< orphan*/  sa_family; } ;
struct TYPE_2__ {int s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct hostent {scalar_t__* h_addr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int PartialIPAddress (char*,struct sockaddr_s*) ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ net_hostport ; 

int WINS_GetAddrFromName( char *name, struct sockaddr_s *addr ){
	struct hostent *hostentry;

	if ( name[0] >= '0' && name[0] <= '9' ) {
		return PartialIPAddress( name, addr );
	}

	hostentry = gethostbyname( name );
	if ( !hostentry ) {
		return -1;
	}

	addr->sa_family = AF_INET;
	( (struct sockaddr_in *)addr )->sin_port = htons( (u_short)net_hostport );
	( (struct sockaddr_in *)addr )->sin_addr.s_addr = *(int *)hostentry->h_addr_list[0];

	return 0;
}