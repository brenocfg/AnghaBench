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
struct socket_calls {int (* getsockname ) (int,int /*<<< orphan*/ *,int*) ;int (* socket ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* close ) (int) ;} ;
struct sockaddr_in6 {int dummy; } ;
typedef  int socklen_t ;
typedef  enum fd_type { ____Placeholder_fd_type } fd_type ;

/* Variables and functions */
 int PF_INET ; 
 int PF_INET6 ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int copysockopts (int,int,struct socket_calls*,struct socket_calls*) ; 
 int fd_getd (int) ; 
 int /*<<< orphan*/  fd_ready ; 
 int fd_rsocket ; 
 int /*<<< orphan*/  fd_store (int,int,int,int /*<<< orphan*/ ) ; 
 struct socket_calls real ; 
 struct socket_calls rs ; 
 int stub1 (int,int /*<<< orphan*/ *,int*) ; 
 int stub2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int) ; 

__attribute__((used)) static int transpose_socket(int socket, enum fd_type new_type)
{
	socklen_t len = 0;
	int sfd, dfd, param, ret;
	struct socket_calls *sapi, *dapi;

	sfd = fd_getd(socket);
	if (new_type == fd_rsocket) {
		dapi = &rs;
		sapi = &real;
	} else {
		dapi = &real;
		sapi = &rs;
	}

	ret = sapi->getsockname(sfd, NULL, &len);
	if (ret)
		return ret;

	param = (len == sizeof(struct sockaddr_in6)) ? PF_INET6 : PF_INET;
	dfd = dapi->socket(param, SOCK_STREAM, 0);
	if (dfd < 0)
		return dfd;

	ret = copysockopts(dfd, sfd, dapi, sapi);
	if (ret)
		goto err;

	fd_store(socket, dfd, new_type, fd_ready);
	return dfd;

err:
	dapi->close(dfd);
	return ret;
}