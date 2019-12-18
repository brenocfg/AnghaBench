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
typedef  int /*<<< orphan*/  uint32_t ;
struct path_ctx {int /*<<< orphan*/  fd; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  rv ;
typedef  int /*<<< orphan*/  len ;
struct TYPE_4__ {int length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ heim_idata ;
typedef  int /*<<< orphan*/ * heim_icred ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int net_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int net_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
unix_socket_ipc(void *ctx,
		const heim_idata *req, heim_idata *rep,
		heim_icred *cred)
{
    struct path_ctx *s = ctx;
    uint32_t len = htonl(req->length);
    uint32_t rv;
    int retval;

    if (cred)
	*cred = NULL;

    rep->data = NULL;
    rep->length = 0;

    if (net_write(s->fd, &len, sizeof(len)) != sizeof(len))
	return -1;
    if (net_write(s->fd, req->data, req->length) != (ssize_t)req->length)
	return -1;

    if (net_read(s->fd, &len, sizeof(len)) != sizeof(len))
	return -1;
    if (net_read(s->fd, &rv, sizeof(rv)) != sizeof(rv))
	return -1;
    retval = ntohl(rv);

    rep->length = ntohl(len);
    if (rep->length > 0) {
	rep->data = malloc(rep->length);
	if (rep->data == NULL)
	    return -1;
	if (net_read(s->fd, rep->data, rep->length) != (ssize_t)rep->length)
	    return -1;
    } else
	rep->data = NULL;

    return retval;
}