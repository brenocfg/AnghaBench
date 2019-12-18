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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int socklen_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 scalar_t__ getnameinfo (struct sockaddr*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Sys_SockaddrToString(char *dest, int destlen, struct sockaddr *input)
{
	socklen_t inputlen;

	if (input->sa_family == AF_INET6)
		inputlen = sizeof(struct sockaddr_in6);
	else
		inputlen = sizeof(struct sockaddr_in);

	if(getnameinfo(input, inputlen, dest, destlen, NULL, 0, NI_NUMERICHOST) && destlen > 0)
		*dest = '\0';
}