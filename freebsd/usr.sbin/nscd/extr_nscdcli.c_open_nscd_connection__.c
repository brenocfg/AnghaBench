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
struct nscd_connection_params {int /*<<< orphan*/  socket_path; } ;
struct nscd_connection_ {int sockfd; int write_queue; int read_queue; } ;
struct kevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EVFILT_WRITE ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TRACE_IN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_OUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct nscd_connection_* calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kevent (int,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* kqueue () ; 
 int /*<<< orphan*/  open_nscd_connection ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

struct nscd_connection_ *
open_nscd_connection__(struct nscd_connection_params const *params)
{
	struct nscd_connection_ *retval;
	struct kevent eventlist;
	struct sockaddr_un	client_address;
	int client_address_len, client_socket;
	int res;

	TRACE_IN(open_nscd_connection);
	assert(params != NULL);

	client_socket = socket(PF_LOCAL, SOCK_STREAM, 0);
	client_address.sun_family = PF_LOCAL;
	strlcpy(client_address.sun_path, params->socket_path,
		sizeof(client_address.sun_path));
	client_address_len = sizeof(client_address.sun_family) +
		strlen(client_address.sun_path) + 1;

	res = connect(client_socket, (struct sockaddr *)&client_address,
		client_address_len);
	if (res == -1) {
		close(client_socket);
		TRACE_OUT(open_nscd_connection);
		return (NULL);
	}
	fcntl(client_socket, F_SETFL, O_NONBLOCK);

	retval = calloc(1, sizeof(*retval));
	assert(retval != NULL);

	retval->sockfd = client_socket;

	retval->write_queue = kqueue();
	assert(retval->write_queue != -1);

	EV_SET(&eventlist, retval->sockfd, EVFILT_WRITE, EV_ADD,
		0, 0, NULL);
	res = kevent(retval->write_queue, &eventlist, 1, NULL, 0, NULL);

	retval->read_queue = kqueue();
	assert(retval->read_queue != -1);

	EV_SET(&eventlist, retval->sockfd, EVFILT_READ, EV_ADD,
		0, 0, NULL);
	res = kevent(retval->read_queue, &eventlist, 1, NULL, 0, NULL);

	TRACE_OUT(open_nscd_connection);
	return (retval);
}