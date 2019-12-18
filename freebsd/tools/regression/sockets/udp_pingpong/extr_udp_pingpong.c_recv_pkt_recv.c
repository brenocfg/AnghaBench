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
struct timespec {int dummy; } ;
struct test_ctx {int /*<<< orphan*/ * fds; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_clock_type (struct test_ctx*) ; 
 scalar_t__ recv (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
recv_pkt_recv(struct test_ctx *tcp, int fdidx, const char *face, void *buf,
  size_t rlen, struct timespec *tp)
{
    ssize_t rval;

    rval = recv(tcp->fds[fdidx], buf, rlen, 0);
    clock_gettime(get_clock_type(tcp), tp);
    if (rval < 0) {
        err(1, "%s: %s: recv(%d)", tcp->name, face, tcp->fds[fdidx]);
    }
    if (rval < (ssize_t)rlen) {
        errx(1, "%s: %s: recv(%d): short recv", tcp->name, face,
            tcp->fds[fdidx]);
    }
}