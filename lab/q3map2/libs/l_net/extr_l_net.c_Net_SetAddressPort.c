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
typedef  int /*<<< orphan*/  sockaddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  ip; } ;
typedef  TYPE_1__ address_t ;

/* Variables and functions */
 int /*<<< orphan*/  WINS_AddrToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WINS_SetSocketPort (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WINS_StringToAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Net_SetAddressPort( address_t *address, int port ){
	sockaddr_t addr;

	WINS_StringToAddr( address->ip, &addr );
	WINS_SetSocketPort( &addr, port );
	strcpy( address->ip, WINS_AddrToString( &addr ) );
}