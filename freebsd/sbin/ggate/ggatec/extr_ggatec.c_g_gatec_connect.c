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
 int /*<<< orphan*/  GGATE_FLAG_RECV ; 
 int /*<<< orphan*/  GGATE_FLAG_SEND ; 
 int /*<<< orphan*/  arc4random () ; 
 int handshake (int /*<<< orphan*/ ) ; 
 int recvfd ; 
 int sendfd ; 
 int /*<<< orphan*/  token ; 

__attribute__((used)) static int
g_gatec_connect(void)
{

	token = arc4random();
	/*
	 * Our receive descriptor is connected to the send descriptor on the
	 * server side.
	 */
	recvfd = handshake(GGATE_FLAG_SEND);
	if (recvfd == -1)
		return (0);
	/*
	 * Our send descriptor is connected to the receive descriptor on the
	 * server side.
	 */
	sendfd = handshake(GGATE_FLAG_RECV);
	if (sendfd == -1)
		return (0);
	return (1);
}