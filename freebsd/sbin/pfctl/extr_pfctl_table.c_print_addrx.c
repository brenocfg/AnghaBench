#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sa_family; int sa_len; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin_addr; } ;
union sockaddr_union {TYPE_3__ sa; TYPE_2__ sin6; TYPE_1__ sin; } ;
struct pfr_addr {unsigned int pfra_fback; scalar_t__ pfra_af; unsigned int pfra_net; int /*<<< orphan*/  pfra_ip6addr; int /*<<< orphan*/  pfra_ip4addr; scalar_t__ pfra_not; int /*<<< orphan*/  pfra_u; } ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  host ;
typedef  int /*<<< orphan*/  fb ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NAMEREQD ; 
 unsigned int PFR_FB_NONE ; 
 int /*<<< orphan*/  bzero (union sockaddr_union*,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ getnameinfo (TYPE_3__*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntop (scalar_t__,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strlcpy (char*,char*,int) ; 

void
print_addrx(struct pfr_addr *ad, struct pfr_addr *rad, int dns)
{
	char		ch, buf[256] = "{error}";
	char		fb[] = { ' ', 'M', 'A', 'D', 'C', 'Z', 'X', ' ', 'Y', ' ' };
	unsigned int	fback, hostnet;

	fback = (rad != NULL) ? rad->pfra_fback : ad->pfra_fback;
	ch = (fback < sizeof(fb)/sizeof(*fb)) ? fb[fback] : '?';
	hostnet = (ad->pfra_af == AF_INET6) ? 128 : 32;
	inet_ntop(ad->pfra_af, &ad->pfra_u, buf, sizeof(buf));
	printf("%c %c%s", ch, (ad->pfra_not?'!':' '), buf);
	if (ad->pfra_net < hostnet)
		printf("/%d", ad->pfra_net);
	if (rad != NULL && fback != PFR_FB_NONE) {
		if (strlcpy(buf, "{error}", sizeof(buf)) >= sizeof(buf))
			errx(1, "print_addrx: strlcpy");
		inet_ntop(rad->pfra_af, &rad->pfra_u, buf, sizeof(buf));
		printf("\t%c%s", (rad->pfra_not?'!':' '), buf);
		if (rad->pfra_net < hostnet)
			printf("/%d", rad->pfra_net);
	}
	if (rad != NULL && fback == PFR_FB_NONE)
		printf("\t nomatch");
	if (dns && ad->pfra_net == hostnet) {
		char host[NI_MAXHOST];
		union sockaddr_union sa;

		strlcpy(host, "?", sizeof(host));
		bzero(&sa, sizeof(sa));
		sa.sa.sa_family = ad->pfra_af;
		if (sa.sa.sa_family == AF_INET) {
			sa.sa.sa_len = sizeof(sa.sin);
			sa.sin.sin_addr = ad->pfra_ip4addr;
		} else {
			sa.sa.sa_len = sizeof(sa.sin6);
			sa.sin6.sin6_addr = ad->pfra_ip6addr;
		}
		if (getnameinfo(&sa.sa, sa.sa.sa_len, host, sizeof(host),
		    NULL, 0, NI_NAMEREQD) == 0)
			printf("\t(%s)", host);
	}
	printf("\n");
}