#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct addrinfo {int ai_family; int ai_flags; int /*<<< orphan*/ * ai_next; int /*<<< orphan*/  ai_socktype; } ;
typedef  int /*<<< orphan*/  hints ;
struct TYPE_2__ {int address_family; } ;

/* Variables and functions */
 int AF_UNSPEC ; 
 int AI_NUMERICHOST ; 
 int AI_NUMERICSERV ; 
 int NI_MAXSERV ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int default_ssh_port () ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ is_addr_fast (char const*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ options ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
is_addr(const char *name)
{
	char strport[NI_MAXSERV];
	struct addrinfo hints, *res;

	if (is_addr_fast(name))
		return 1;

	snprintf(strport, sizeof strport, "%u", default_ssh_port());
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = options.address_family == -1 ?
	    AF_UNSPEC : options.address_family;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICHOST|AI_NUMERICSERV;
	if (getaddrinfo(name, strport, &hints, &res) != 0)
		return 0;
	if (res == NULL || res->ai_next != NULL) {
		freeaddrinfo(res);
		return 0;
	}
	freeaddrinfo(res);
	return 1;
}