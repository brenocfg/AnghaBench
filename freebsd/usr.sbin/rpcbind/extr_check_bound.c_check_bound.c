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
struct sockaddr {int dummy; } ;
struct netbuf {struct netbuf* buf; int /*<<< orphan*/  len; } ;
struct fdlist {scalar_t__ check_binding; int /*<<< orphan*/  nconf; } ;
typedef  scalar_t__ bool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int __rpc_nconf2fd (int /*<<< orphan*/ ) ; 
 int bind (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct netbuf*) ; 
 struct netbuf* uaddr2taddr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool_t
check_bound(struct fdlist *fdl, char *uaddr)
{
	int fd;
	struct netbuf *na;
	int ans;

	if (fdl->check_binding == FALSE)
		return (TRUE);

	na = uaddr2taddr(fdl->nconf, uaddr);
	if (!na)
		return (TRUE); /* punt, should never happen */

	fd = __rpc_nconf2fd(fdl->nconf);
	if (fd < 0) {
		free(na->buf);
		free(na);
		return (TRUE);
	}

	ans = bind(fd, (struct sockaddr *)na->buf, na->len);

	close(fd);
	free(na->buf);
	free(na);

	return (ans == 0 ? FALSE : TRUE);
}