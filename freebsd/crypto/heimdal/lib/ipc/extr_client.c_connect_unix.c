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
struct path_ctx {scalar_t__ fd; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ connect (scalar_t__,struct sockaddr*,int) ; 
 int errno ; 
 int /*<<< orphan*/  rk_cloexec (scalar_t__) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
connect_unix(struct path_ctx *s)
{
    struct sockaddr_un addr;

    addr.sun_family = AF_UNIX;
    strlcpy(addr.sun_path, s->path, sizeof(addr.sun_path));

    s->fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (s->fd < 0)
	return errno;
    rk_cloexec(s->fd);

    if (connect(s->fd, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
	close(s->fd);
	return errno;
    }

    return 0;
}