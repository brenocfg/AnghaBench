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

/* Variables and functions */
 int /*<<< orphan*/  MSG_PEEK ; 
 int net_acceptsocket ; 
 scalar_t__ recvfrom (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int WINS_CheckNewConnections( void ){
	char buf[4];

	if ( net_acceptsocket == -1 ) {
		return -1;
	}

	if ( recvfrom( net_acceptsocket, buf, 4, MSG_PEEK, NULL, NULL ) > 0 ) {
		return net_acceptsocket;
	}
	return -1;
}