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
struct timespec {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
struct runtime_env {int queue; int /*<<< orphan*/  sockfd; } ;
struct kevent {int dummy; } ;
struct configuration {int force_unlink; int /*<<< orphan*/  socket_mode; int /*<<< orphan*/  socket_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int EV_ADD ; 
 int EV_ONESHOT ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  LOG_ERR_2 (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_MSG_2 (char*,char*,...) ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TRACE_IN (struct runtime_env* (*) (struct configuration*)) ; 
 int /*<<< orphan*/  TRACE_OUT (struct runtime_env* (*) (struct configuration*)) ; 
 int /*<<< orphan*/  assert (int) ; 
 int bind (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 struct runtime_env* calloc (int,int) ; 
 int /*<<< orphan*/  chmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct runtime_env*) ; 
 int /*<<< orphan*/  kevent (int,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timespec*) ; 
 int kqueue () ; 
 int /*<<< orphan*/  listen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct timespec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct runtime_env *
init_runtime_env(struct configuration *config)
{
	int serv_addr_len;
	struct sockaddr_un serv_addr;

	struct kevent eventlist;
	struct timespec timeout;

	struct runtime_env *retval;

	TRACE_IN(init_runtime_env);
	retval = calloc(1, sizeof(*retval));
	assert(retval != NULL);

	retval->sockfd = socket(PF_LOCAL, SOCK_STREAM, 0);

	if (config->force_unlink == 1)
		unlink(config->socket_path);

	memset(&serv_addr, 0, sizeof(struct sockaddr_un));
	serv_addr.sun_family = PF_LOCAL;
	strlcpy(serv_addr.sun_path, config->socket_path,
		sizeof(serv_addr.sun_path));
	serv_addr_len = sizeof(serv_addr.sun_family) +
		strlen(serv_addr.sun_path) + 1;

	if (bind(retval->sockfd, (struct sockaddr *)&serv_addr,
		serv_addr_len) == -1) {
		close(retval->sockfd);
		free(retval);

		LOG_ERR_2("runtime environment", "can't bind socket to path: "
			"%s", config->socket_path);
		TRACE_OUT(init_runtime_env);
		return (NULL);
	}
	LOG_MSG_2("runtime environment", "using socket %s",
		config->socket_path);

	/*
	 * Here we're marking socket as non-blocking and setting its backlog
	 * to the maximum value
	 */
	chmod(config->socket_path, config->socket_mode);
	listen(retval->sockfd, -1);
	fcntl(retval->sockfd, F_SETFL, O_NONBLOCK);

	retval->queue = kqueue();
	assert(retval->queue != -1);

	EV_SET(&eventlist, retval->sockfd, EVFILT_READ, EV_ADD | EV_ONESHOT,
		0, 0, 0);
	memset(&timeout, 0, sizeof(struct timespec));
	kevent(retval->queue, &eventlist, 1, NULL, 0, &timeout);

	LOG_MSG_2("runtime environment", "successfully initialized");
	TRACE_OUT(init_runtime_env);
	return (retval);
}