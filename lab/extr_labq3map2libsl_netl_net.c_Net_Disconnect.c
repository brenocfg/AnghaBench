#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  Net_FreeSocket (TYPE_1__*) ; 
 int /*<<< orphan*/  WINS_CloseSocket (int /*<<< orphan*/ ) ; 

void Net_Disconnect( socket_t *sock ){
	WINS_CloseSocket( sock->socket );
	Net_FreeSocket( sock );
}