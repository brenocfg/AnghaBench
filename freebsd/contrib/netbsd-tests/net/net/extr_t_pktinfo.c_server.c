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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_1__ sin_addr; scalar_t__ sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  one ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IP_PKTINFO ; 
 int /*<<< orphan*/  IP_RECVPKTINFO ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int bind (int,struct sockaddr const*,int) ; 
 int getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
server(struct sockaddr_in *sin) {
	int s, one;
	socklen_t len = sizeof(*sin);

	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		ERR("socket");

	memset(sin, 0, len);
	sin->sin_family = AF_INET;
	sin->sin_len = len;
	sin->sin_port = 0;
	sin->sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	if (bind(s, (const struct sockaddr *)sin, len) == -1)
		ERR("bind");

	if (getsockname(s, (struct sockaddr *)sin, &len) == -1)
		ERR("getsockname");

	one = 1;
	if (setsockopt(s, IPPROTO_IP, IP_PKTINFO, &one, sizeof(one)) == -1)
		ERR("setsockopt");
	if (setsockopt(s, IPPROTO_IP, IP_RECVPKTINFO, &one, sizeof(one)) == -1)
		ERR("setsockopt");

	return s;
}