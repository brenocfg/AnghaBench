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
struct tcp_ctx {scalar_t__ tc_magic; int /*<<< orphan*/  tc_fd; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  PJDLOG_VERIFY (int) ; 
 scalar_t__ TCP_CTX_MAGIC ; 
 scalar_t__ getpeername (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ snprintf (char*,size_t,char*,struct sockaddr_storage*) ; 
 int /*<<< orphan*/  sockaddr_to_string (struct sockaddr_storage*,char*,size_t) ; 
 size_t strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void
tcp_remote_address(const void *ctx, char *addr, size_t size)
{
	const struct tcp_ctx *tctx = ctx;
	struct sockaddr_storage sa;
	socklen_t salen;

	PJDLOG_ASSERT(tctx != NULL);
	PJDLOG_ASSERT(tctx->tc_magic == TCP_CTX_MAGIC);

	salen = sizeof(sa);
	if (getpeername(tctx->tc_fd, (struct sockaddr *)&sa, &salen) < 0) {
		PJDLOG_VERIFY(strlcpy(addr, "N/A", size) < size);
		return;
	}
#ifdef __FreeBSD__
	PJDLOG_VERIFY(snprintf(addr, size, "tcp://%S", &sa) < (ssize_t)size);
#else
	strlcpy(addr, "tcp://", size);
	if (size > 6)
		sockaddr_to_string(&sa, addr + 6, size - 6);
#endif
}