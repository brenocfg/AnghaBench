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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct in6_addr {int /*<<< orphan*/  s6_addr; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int DNS_ERR_CANCEL ; 
 int DNS_ERR_NONE ; 
#define  DNS_IPv4_A 130 
#define  DNS_IPv6_AAAA 129 
#define  DNS_PTR 128 
 int /*<<< orphan*/  INET6_ADDRSTRLEN ; 
 int dns_got_cancel ; 
 scalar_t__ dns_ok ; 
 int /*<<< orphan*/  event_loopexit (int /*<<< orphan*/ *) ; 
 char* evutil_inet_ntop (int /*<<< orphan*/ ,struct in6_addr*,char*,int) ; 
 int /*<<< orphan*/  htonl (int) ; 
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int n_server_responses ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void
dns_server_gethostbyname_cb(int result, char type, int count, int ttl,
    void *addresses, void *arg)
{
	if (result == DNS_ERR_CANCEL) {
		if (arg != (void*)(char*)90909) {
			printf("Unexpected cancelation");
			dns_ok = 0;
		}
		dns_got_cancel = 1;
		goto out;
	}
	if (result != DNS_ERR_NONE) {
		printf("Unexpected result %d. ", result);
		dns_ok = 0;
		goto out;
	}
	if (count != 1) {
		printf("Unexpected answer count %d. ", count);
		dns_ok = 0;
		goto out;
	}
	switch (type) {
	case DNS_IPv4_A: {
		struct in_addr *in_addrs = addresses;
		if (in_addrs[0].s_addr != htonl(0xc0a80b0bUL) || ttl != 12345) {
			printf("Bad IPv4 response \"%s\" %d. ",
					inet_ntoa(in_addrs[0]), ttl);
			dns_ok = 0;
			goto out;
		}
		break;
	}
	case DNS_IPv6_AAAA: {
#if defined (EVENT__HAVE_STRUCT_IN6_ADDR) && defined(EVENT__HAVE_INET_NTOP) && defined(INET6_ADDRSTRLEN)
		struct in6_addr *in6_addrs = addresses;
		char buf[INET6_ADDRSTRLEN+1];
		if (memcmp(&in6_addrs[0].s6_addr, "abcdefghijklmnop", 16)
		    || ttl != 123) {
			const char *b = evutil_inet_ntop(AF_INET6, &in6_addrs[0],buf,sizeof(buf));
			printf("Bad IPv6 response \"%s\" %d. ", b, ttl);
			dns_ok = 0;
			goto out;
		}
#endif
		break;
	}
	case DNS_PTR: {
		char **addrs = addresses;
		if (arg != (void*)6) {
			if (strcmp(addrs[0], "ZZ.EXAMPLE.COM") ||
			    ttl != 54321) {
				printf("Bad PTR response \"%s\" %d. ",
				    addrs[0], ttl);
				dns_ok = 0;
				goto out;
			}
		} else {
			if (strcmp(addrs[0], "ZZ-INET6.EXAMPLE.COM") ||
			    ttl != 54322) {
				printf("Bad ipv6 PTR response \"%s\" %d. ",
				    addrs[0], ttl);
				dns_ok = 0;
				goto out;
			}
		}
		break;
	}
	default:
		printf("Bad response type %d. ", type);
		dns_ok = 0;
	}
 out:
	if (++n_server_responses == 3) {
		event_loopexit(NULL);
	}
}