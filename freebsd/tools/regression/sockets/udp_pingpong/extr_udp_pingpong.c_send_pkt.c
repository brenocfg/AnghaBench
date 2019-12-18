#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct test_ctx {int nsent; int /*<<< orphan*/ * fds; int /*<<< orphan*/  name; TYPE_2__* test_pkts; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {TYPE_1__* tss; } ;
struct TYPE_3__ {int /*<<< orphan*/  sent; } ;

/* Variables and functions */
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_clock_type (struct test_ctx*) ; 
 scalar_t__ send (int /*<<< orphan*/ ,TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
send_pkt(struct test_ctx *tcp, int pnum, int fdidx, const char *face)
{
    ssize_t r;
    size_t slen;

    slen = sizeof(tcp->test_pkts[pnum]);
    clock_gettime(get_clock_type(tcp), &tcp->test_pkts[pnum].tss[fdidx].sent);
    r = send(tcp->fds[fdidx], &tcp->test_pkts[pnum], slen, 0);
    if (r < 0) {
        err(1, "%s: %s: send(%d)", tcp->name, face, tcp->fds[fdidx]);
    }
    if (r < (ssize_t)slen) {
        errx(1, "%s: %s: send(%d): short send", tcp->name, face,
          tcp->fds[fdidx]);
    }
    tcp->nsent += 1;
}