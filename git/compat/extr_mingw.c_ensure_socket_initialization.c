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
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 scalar_t__ WSACleanup ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atexit (void (*) ()) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ensure_socket_initialization(void)
{
	WSADATA wsa;
	static int initialized = 0;

	if (initialized)
		return;

	if (WSAStartup(MAKEWORD(2,2), &wsa))
		die("unable to initialize winsock subsystem, error %d",
			WSAGetLastError());

	atexit((void(*)(void)) WSACleanup);
	initialized = 1;
}