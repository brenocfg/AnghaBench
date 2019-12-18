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
struct tube {int sr; int sw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ calloc (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  fd_set_nonblock (int) ; 
 int /*<<< orphan*/  free (struct tube*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  tube_delete (struct tube*) ; 

struct tube* tube_create(void)
{
	struct tube* tube = (struct tube*)calloc(1, sizeof(*tube));
	int sv[2];
	if(!tube) {
		int err = errno;
		log_err("tube_create: out of memory");
		errno = err;
		return NULL;
	}
	tube->sr = -1;
	tube->sw = -1;
	if(socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
		int err = errno;
		log_err("socketpair: %s", strerror(errno));
		free(tube);
		errno = err;
		return NULL;
	}
	tube->sr = sv[0];
	tube->sw = sv[1];
	if(!fd_set_nonblock(tube->sr) || !fd_set_nonblock(tube->sw)) {
		int err = errno;
		log_err("tube: cannot set nonblocking");
		tube_delete(tube);
		errno = err;
		return NULL;
	}
	return tube;
}