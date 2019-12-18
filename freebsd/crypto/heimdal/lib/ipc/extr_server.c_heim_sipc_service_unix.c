#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  un ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
struct client {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  one ;
typedef  TYPE_1__* heim_sipc ;
typedef  int /*<<< orphan*/  heim_ipc_callback ;
struct TYPE_4__ {struct client* mech; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  HEIM_SIPC_TYPE_IPC ; 
 int /*<<< orphan*/  LOCAL_CREDS ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int /*<<< orphan*/  UNIX_SOCKET ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  chmod (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int heim_sipc_stream_listener (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,TYPE_1__**) ; 
 scalar_t__ listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_set_reuseaddr (int,int) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int
heim_sipc_service_unix(const char *service,
		       heim_ipc_callback callback,
		       void *user, heim_sipc *ctx)
{
    struct sockaddr_un un;
    int fd, ret;

    un.sun_family = AF_UNIX;

    snprintf(un.sun_path, sizeof(un.sun_path),
	     "/var/run/.heim_%s-socket", service);
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0)
	return errno;

    socket_set_reuseaddr(fd, 1);
#ifdef LOCAL_CREDS
    {
	int one = 1;
	setsockopt(fd, 0, LOCAL_CREDS, (void *)&one, sizeof(one));
    }
#endif

    unlink(un.sun_path);

    if (bind(fd, (struct sockaddr *)&un, sizeof(un)) < 0) {
	close(fd);
	return errno;
    }

    if (listen(fd, SOMAXCONN) < 0) {
	close(fd);
	return errno;
    }

    chmod(un.sun_path, 0666);

    ret = heim_sipc_stream_listener(fd, HEIM_SIPC_TYPE_IPC,
				    callback, user, ctx);
    if (ret == 0) {
	struct client *c = (*ctx)->mech;
	c->flags |= UNIX_SOCKET;
    }

    return ret;
}