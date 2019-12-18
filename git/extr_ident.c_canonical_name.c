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
struct strbuf {int dummy; } ;
struct hostent {scalar_t__ h_name; } ;
struct addrinfo {scalar_t__ ai_canonname; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CANONNAME ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  getaddrinfo (char const*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 struct hostent* gethostbyname (char const*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,char,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,scalar_t__) ; 
 scalar_t__ strchr (scalar_t__,char) ; 

__attribute__((used)) static int canonical_name(const char *host, struct strbuf *out)
{
	int status = -1;

#ifndef NO_IPV6
	struct addrinfo hints, *ai;
	memset (&hints, '\0', sizeof (hints));
	hints.ai_flags = AI_CANONNAME;
	if (!getaddrinfo(host, NULL, &hints, &ai)) {
		if (ai && ai->ai_canonname && strchr(ai->ai_canonname, '.')) {
			strbuf_addstr(out, ai->ai_canonname);
			status = 0;
		}
		freeaddrinfo(ai);
	}
#else
	struct hostent *he = gethostbyname(host);
	if (he && strchr(he->h_name, '.')) {
		strbuf_addstr(out, he->h_name);
		status = 0;
	}
#endif /* NO_IPV6 */

	return status;
}