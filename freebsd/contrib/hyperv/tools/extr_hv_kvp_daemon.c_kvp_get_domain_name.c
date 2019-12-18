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
struct addrinfo {char* ai_canonname; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AI_CANONNAME ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static int
kvp_get_domain_name(char *buffer, int length)
{
	struct addrinfo hints, *info;
	int error = 0;

	gethostname(buffer, length);
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;    /* Get only ipv4 addrinfo. */
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_CANONNAME;

	error = getaddrinfo(buffer, NULL, &hints, &info);
	if (error != 0) {
		strlcpy(buffer, "getaddrinfo failed\n", length);
		return (error);
	}
	strlcpy(buffer, info->ai_canonname, length);
	freeaddrinfo(info);
	return (error);
}