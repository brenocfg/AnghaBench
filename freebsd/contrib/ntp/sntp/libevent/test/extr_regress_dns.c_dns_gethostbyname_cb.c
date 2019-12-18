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
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct event_base {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int DNS_ERR_NONE ; 
 int DNS_ERR_TIMEOUT ; 
#define  DNS_IPv4_A 130 
#define  DNS_IPv6_AAAA 129 
#define  DNS_PTR 128 
 int /*<<< orphan*/  INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 char dns_err ; 
 char dns_ok ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_base_loopexit (struct event_base*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_loopexit (int /*<<< orphan*/ *) ; 
 char* evutil_inet_ntop (int /*<<< orphan*/ ,struct in6_addr*,char*,int) ; 
 int /*<<< orphan*/  inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dns_gethostbyname_cb(int result, char type, int count, int ttl,
    void *addresses, void *arg)
{
	dns_ok = dns_err = 0;

	if (result == DNS_ERR_TIMEOUT) {
		printf("[Timed out] ");
		dns_err = result;
		goto out;
	}

	if (result != DNS_ERR_NONE) {
		printf("[Error code %d] ", result);
		goto out;
	}

	TT_BLATHER(("type: %d, count: %d, ttl: %d: ", type, count, ttl));

	switch (type) {
	case DNS_IPv6_AAAA: {
#if defined(EVENT__HAVE_STRUCT_IN6_ADDR) && defined(EVENT__HAVE_INET_NTOP) && defined(INET6_ADDRSTRLEN)
		struct in6_addr *in6_addrs = addresses;
		char buf[INET6_ADDRSTRLEN+1];
		int i;
		/* a resolution that's not valid does not help */
		if (ttl < 0)
			goto out;
		for (i = 0; i < count; ++i) {
			const char *b = evutil_inet_ntop(AF_INET6, &in6_addrs[i], buf,sizeof(buf));
			if (b)
				TT_BLATHER(("%s ", b));
			else
				TT_BLATHER(("%s ", strerror(errno)));
		}
#endif
		break;
	}
	case DNS_IPv4_A: {
		struct in_addr *in_addrs = addresses;
		int i;
		/* a resolution that's not valid does not help */
		if (ttl < 0)
			goto out;
		for (i = 0; i < count; ++i)
			TT_BLATHER(("%s ", inet_ntoa(in_addrs[i])));
		break;
	}
	case DNS_PTR:
		/* may get at most one PTR */
		if (count != 1)
			goto out;

		TT_BLATHER(("%s ", *(char **)addresses));
		break;
	default:
		goto out;
	}

	dns_ok = type;

out:
	if (arg == NULL)
		event_loopexit(NULL);
	else
		event_base_loopexit((struct event_base *)arg, NULL);
}