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
struct tcp_ctx {int /*<<< orphan*/  tc_fd; } ;
struct sockaddr_storage {int /*<<< orphan*/  ss_len; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_SIDE_CLIENT ; 
 int bind (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int tcp_addr (char const*,int /*<<< orphan*/ ,struct sockaddr_storage*) ; 
 int /*<<< orphan*/  tcp_close (struct tcp_ctx*) ; 
 int tcp_setup_new (char const*,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static int
tcp_client(const char *srcaddr, const char *dstaddr, void **ctxp)
{
	struct tcp_ctx *tctx;
	struct sockaddr_storage sa;
	int ret;

	ret = tcp_setup_new(dstaddr, TCP_SIDE_CLIENT, ctxp);
	if (ret != 0)
		return (ret);
	tctx = *ctxp;
	if (srcaddr == NULL)
		return (0);
	ret = tcp_addr(srcaddr, 0, &sa);
	if (ret != 0) {
		tcp_close(tctx);
		return (ret);
	}
	if (bind(tctx->tc_fd, (struct sockaddr *)&sa, sa.ss_len) == -1) {
		ret = errno;
		tcp_close(tctx);
		return (ret);
	}
	return (0);
}