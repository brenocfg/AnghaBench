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
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
struct kevent {int dummy; } ;
struct cached_connection_params {int /*<<< orphan*/  socket_path; } ;
struct cached_connection_ {int sockfd; int write_queue; int read_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EVFILT_WRITE ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int SOCK_CLOEXEC ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  _close (int) ; 
 int _connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  _fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _kevent (int,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* kqueue () ; 
 struct cached_connection_* malloc (int) ; 
 int /*<<< orphan*/  memset (struct cached_connection_*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct cached_connection_ *
__open_cached_connection(struct cached_connection_params const *params)
{
	struct cached_connection_ *retval;
	struct kevent eventlist;
	struct sockaddr_un client_address;
	int client_address_len, client_socket;
	int res;

	assert(params != NULL);

	client_socket = _socket(PF_LOCAL, SOCK_STREAM | SOCK_CLOEXEC, 0);
	client_address.sun_family = PF_LOCAL;
	strncpy(client_address.sun_path, params->socket_path,
	    sizeof(client_address.sun_path));
	client_address_len = sizeof(client_address.sun_family) +
	    strlen(client_address.sun_path) + 1;

	res = _connect(client_socket, (struct sockaddr *)&client_address,
	    client_address_len);
	if (res == -1) {
		_close(client_socket);
		return (NULL);
	}
	_fcntl(client_socket, F_SETFL, O_NONBLOCK);

	retval = malloc(sizeof(struct cached_connection_));
	assert(retval != NULL);
	memset(retval, 0, sizeof(struct cached_connection_));

	retval->sockfd = client_socket;

	retval->write_queue = kqueue();
	assert(retval->write_queue != -1);

	EV_SET(&eventlist, retval->sockfd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
	res = _kevent(retval->write_queue, &eventlist, 1, NULL, 0, NULL);

	retval->read_queue = kqueue();
	assert(retval->read_queue != -1);

	EV_SET(&eventlist, retval->sockfd, EVFILT_READ, EV_ADD, 0, 0, NULL);
	res = _kevent(retval->read_queue, &eventlist, 1, NULL, 0, NULL);

	return (retval);
}