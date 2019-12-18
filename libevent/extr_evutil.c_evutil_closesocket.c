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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int close (int /*<<< orphan*/ ) ; 
 int closesocket (int /*<<< orphan*/ ) ; 

int
evutil_closesocket(evutil_socket_t sock)
{
#ifndef _WIN32
	return close(sock);
#else
	return closesocket(sock);
#endif
}