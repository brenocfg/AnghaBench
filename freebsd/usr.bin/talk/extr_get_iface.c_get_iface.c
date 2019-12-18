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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; struct in_addr sin_addr; void* sin_port; void* sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;

/* Variables and functions */
 void* AF_INET ; 
 scalar_t__ EADDRINUSE ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  memcpy (struct in_addr*,struct in_addr*,int) ; 
 int ntohs (void*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
get_iface(struct in_addr *dst, struct in_addr *iface)
{
	static struct sockaddr_in local;
	struct sockaddr_in remote;
	socklen_t namelen;
	int s, rv;

	memcpy(&remote.sin_addr, dst, sizeof remote.sin_addr);
	remote.sin_port = htons(60000);
	remote.sin_family = AF_INET;
	remote.sin_len = sizeof remote;

	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(60000);
	local.sin_family = AF_INET;
	local.sin_len = sizeof local;

	s = socket(PF_INET, SOCK_DGRAM, 0);
	if (s < 0)
		return -1;

	do {
		rv = bind(s, (struct sockaddr *)&local, sizeof local);
		local.sin_port = htons(ntohs(local.sin_port) + 1);
	} while(rv < 0 && errno == EADDRINUSE);

	if (rv < 0) {
		close(s);
		return -1;
	}

	do {
		rv = connect(s, (struct sockaddr *)&remote, sizeof remote);
		remote.sin_port = htons(ntohs(remote.sin_port) + 1);
	} while(rv < 0 && errno == EADDRINUSE);

	if (rv < 0) {
		close(s);
		return -1;
	}

	namelen = sizeof local;
	rv = getsockname(s, (struct sockaddr *)&local, &namelen);
	close(s);
	if (rv < 0)
		return -1;

	memcpy(iface, &local.sin_addr, sizeof local.sin_addr);
	return 0;
}