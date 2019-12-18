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
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ verb ; 
 char* wsa_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_sock_err(const char* msg)
{
#ifndef USE_WINSOCK
	if(verb) printf("%s: %s\n", msg, strerror(errno));
#else
	if(verb) printf("%s: %s\n", msg, wsa_strerror(WSAGetLastError()));
#endif
}