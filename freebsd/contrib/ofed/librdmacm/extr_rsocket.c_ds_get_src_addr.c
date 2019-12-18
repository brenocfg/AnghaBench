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
struct TYPE_2__ {int /*<<< orphan*/  sin_port; } ;
union socket_addr {TYPE_1__ sin; int /*<<< orphan*/  sa; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct rsocket {int udp_sock; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr const*,int) ; 
 int getsockname (int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  rs_any_addr (union socket_addr*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds_get_src_addr(struct rsocket *rs,
			   const struct sockaddr *dest_addr, socklen_t dest_len,
			   union socket_addr *src_addr, socklen_t *src_len)
{
	int sock, ret;
	__be16 port;

	*src_len = sizeof(*src_addr);
	ret = getsockname(rs->udp_sock, &src_addr->sa, src_len);
	if (ret || !rs_any_addr(src_addr))
		return ret;

	port = src_addr->sin.sin_port;
	sock = socket(dest_addr->sa_family, SOCK_DGRAM, 0);
	if (sock < 0)
		return sock;

	ret = connect(sock, dest_addr, dest_len);
	if (ret)
		goto out;

	*src_len = sizeof(*src_addr);
	ret = getsockname(sock, &src_addr->sa, src_len);
	src_addr->sin.sin_port = port;
out:
	close(sock);
	return ret;
}