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
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_DEBUG ; 
 scalar_t__ SetSockOpt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ net ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int telnet_debug ; 

__attribute__((used)) static int
togdebug(void)
{
#ifndef	NOT43
    if (net > 0 &&
	(SetSockOpt(net, SOL_SOCKET, SO_DEBUG, telnet_debug)) < 0) {
	    perror("setsockopt (SO_DEBUG)");
    }
#else	/* NOT43 */
    if (telnet_debug) {
	if (net > 0 && SetSockOpt(net, SOL_SOCKET, SO_DEBUG, 1) < 0)
	    perror("setsockopt (SO_DEBUG)");
    } else
	printf("Cannot turn off socket debugging\n");
#endif	/* NOT43 */
    return 1;
}