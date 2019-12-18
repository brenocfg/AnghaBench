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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 char* evutil_inet_ntop (scalar_t__,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  evutil_snprintf (char*,size_t,char*,...) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

const char *
evutil_format_sockaddr_port_(const struct sockaddr *sa, char *out, size_t outlen)
{
	char b[128];
	const char *res=NULL;
	int port;
	if (sa->sa_family == AF_INET) {
		const struct sockaddr_in *sin = (const struct sockaddr_in*)sa;
		res = evutil_inet_ntop(AF_INET, &sin->sin_addr,b,sizeof(b));
		port = ntohs(sin->sin_port);
		if (res) {
			evutil_snprintf(out, outlen, "%s:%d", b, port);
			return out;
		}
	} else if (sa->sa_family == AF_INET6) {
		const struct sockaddr_in6 *sin6 = (const struct sockaddr_in6*)sa;
		res = evutil_inet_ntop(AF_INET6, &sin6->sin6_addr,b,sizeof(b));
		port = ntohs(sin6->sin6_port);
		if (res) {
			evutil_snprintf(out, outlen, "[%s]:%d", b, port);
			return out;
		}
	}

	evutil_snprintf(out, outlen, "<addr with socktype %d>",
	    (int)sa->sa_family);
	return out;
}