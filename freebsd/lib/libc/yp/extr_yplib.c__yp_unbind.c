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
struct sockaddr_in {scalar_t__ sin_family; scalar_t__ sin_port; } ;
struct sockaddr {int dummy; } ;
struct dom_binding {int dom_socket; scalar_t__ dom_local_port; int dom_vers; int /*<<< orphan*/ * dom_client; } ;
typedef  int socklen_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  _close (int) ; 
 int _dup (int) ; 
 int _dup2 (int,int) ; 
 int _getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ypmatch_cache_flush (struct dom_binding*) ; 

__attribute__((used)) static void
_yp_unbind(struct dom_binding *ypb)
{
	struct sockaddr_in check;
	socklen_t checklen = sizeof(struct sockaddr_in);

	if (ypb->dom_client != NULL) {
		/* Check the socket -- may have been hosed by the caller. */
		if (_getsockname(ypb->dom_socket, (struct sockaddr *)&check,
	    	&checklen) == -1 || check.sin_family != AF_INET ||
	    	check.sin_port != ypb->dom_local_port) {
			int save, sock;

			sock = ypb->dom_socket;
			save = _dup(ypb->dom_socket);
			clnt_destroy(ypb->dom_client);
			sock = _dup2(save, sock);
			_close(save);
		} else
			clnt_destroy(ypb->dom_client);
	}

	ypb->dom_client = NULL;
	ypb->dom_socket = -1;
	ypb->dom_vers = -1;
#ifdef YPMATCHCACHE
	ypmatch_cache_flush(ypb);
#endif
}