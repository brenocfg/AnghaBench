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
struct sockaddr_storage {int ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; } ;
struct printf_info {int dummy; } ;
struct __printf_io {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int INET6_ADDRSTRLEN ; 
 int INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  PJDLOG_ABORT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __printf_flush (struct __printf_io*) ; 
 int __printf_out (struct __printf_io*,struct printf_info const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * inet_ntop (int,int /*<<< orphan*/ *,char*,int) ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int
pjdlog_printf_render_sockaddr(struct __printf_io *io,
    const struct printf_info *pi, const void * const *arg)
{
	const struct sockaddr_storage *ss;
	char buf[64];
	int ret;

	ss = *(const struct sockaddr_storage * const *)arg[0];
	switch (ss->ss_family) {
	case AF_INET:
	    {
		char addr[INET_ADDRSTRLEN];
		const struct sockaddr_in *sin;
		unsigned int port;

		sin = (const struct sockaddr_in *)ss;
		port = ntohs(sin->sin_port);
		if (inet_ntop(ss->ss_family, &sin->sin_addr, addr,
		    sizeof(addr)) == NULL) {
			PJDLOG_ABORT("inet_ntop(AF_INET) failed: %s.",
			    strerror(errno));
		}
		snprintf(buf, sizeof(buf), "%s:%u", addr, port);
		break;
	    }
	case AF_INET6:
	    {
		char addr[INET6_ADDRSTRLEN];
		const struct sockaddr_in6 *sin;
		unsigned int port;

		sin = (const struct sockaddr_in6 *)ss;
		port = ntohs(sin->sin6_port);
		if (inet_ntop(ss->ss_family, &sin->sin6_addr, addr,
		    sizeof(addr)) == NULL) {
			PJDLOG_ABORT("inet_ntop(AF_INET6) failed: %s.",
			    strerror(errno));
		}
		snprintf(buf, sizeof(buf), "[%s]:%u", addr, port);
		break;
	    }
	default:
		snprintf(buf, sizeof(buf), "[unsupported family %hhu]",
		    ss->ss_family);
		break;
	}
	ret = __printf_out(io, pi, buf, strlen(buf));
	__printf_flush(io);
	return (ret);
}