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
struct in6_addr {int dummy; } ;
typedef  int ev_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ CHAR_IS_UNRESERVED (char const) ; 
 scalar_t__ EVUTIL_ISXDIGIT_ (char const) ; 
 int /*<<< orphan*/  SUBDELIMS ; 
 int evutil_inet_pton (int /*<<< orphan*/ ,char*,struct in6_addr*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char const) ; 

__attribute__((used)) static int
bracket_addr_ok(const char *s, const char *eos)
{
	if (s + 3 > eos || *s != '[' || *(eos-1) != ']')
		return 0;
	if (s[1] == 'v') {
		/* IPvFuture, or junk.
		   "v" 1*HEXDIG "." 1*( unreserved / sub-delims / ":" )
		 */
		s += 2; /* skip [v */
		--eos;
		if (!EVUTIL_ISXDIGIT_(*s)) /*require at least one*/
			return 0;
		while (s < eos && *s != '.') {
			if (EVUTIL_ISXDIGIT_(*s))
				++s;
			else
				return 0;
		}
		if (*s != '.')
			return 0;
		++s;
		while (s < eos) {
			if (CHAR_IS_UNRESERVED(*s) ||
			    strchr(SUBDELIMS, *s) ||
			    *s == ':')
				++s;
			else
				return 0;
		}
		return 2;
	} else {
		/* IPv6, or junk */
		char buf[64];
		ev_ssize_t n_chars = eos-s-2;
		struct in6_addr in6;
		if (n_chars >= 64) /* way too long */
			return 0;
		memcpy(buf, s+1, n_chars);
		buf[n_chars]='\0';
		return (evutil_inet_pton(AF_INET6,buf,&in6)==1) ? 1 : 0;
	}
}