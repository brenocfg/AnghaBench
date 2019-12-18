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
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct request_info {int /*<<< orphan*/  started; scalar_t__ n_read; } ;
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  BEV_OPT_CLOSE_ON_FREE ; 
 int /*<<< orphan*/  EVUTIL_ERR_CONNECT_RETRIABLE (int) ; 
 int EV_READ ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  base ; 
 int /*<<< orphan*/  bufferevent_enable (struct bufferevent*,int) ; 
 int /*<<< orphan*/  bufferevent_get_output (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct request_info*) ; 
 struct bufferevent* bufferevent_socket_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ connect (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int errno ; 
 int /*<<< orphan*/  errorcb ; 
 int /*<<< orphan*/  evbuffer_add_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ evutil_make_socket_nonblocking (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frob_socket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 struct request_info* malloc (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  readcb ; 
 int /*<<< orphan*/  resource ; 
 int /*<<< orphan*/  socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  total_n_launched ; 

__attribute__((used)) static int
launch_request(void)
{
	evutil_socket_t sock;
	struct sockaddr_in sin;
	struct bufferevent *b;

	struct request_info *ri;

	memset(&sin, 0, sizeof(sin));

	++total_n_launched;

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(0x7f000001);
	sin.sin_port = htons(8080);
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return -1;
	if (evutil_make_socket_nonblocking(sock) < 0) {
		evutil_closesocket(sock);
		return -1;
	}
	frob_socket(sock);
	if (connect(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
		int e = errno;
		if (! EVUTIL_ERR_CONNECT_RETRIABLE(e)) {
			evutil_closesocket(sock);
			return -1;
		}
	}

	ri = malloc(sizeof(*ri));
	if (ri == NULL) {
		printf("Unable to allocate memory in launch_request()\n");
		return -1;
	}
	ri->n_read = 0;
	evutil_gettimeofday(&ri->started, NULL);

	b = bufferevent_socket_new(base, sock, BEV_OPT_CLOSE_ON_FREE);

	bufferevent_setcb(b, readcb, NULL, errorcb, ri);
	bufferevent_enable(b, EV_READ|EV_WRITE);

	evbuffer_add_printf(bufferevent_get_output(b),
	    "GET %s HTTP/1.0\r\n\r\n", resource);

	return 0;
}