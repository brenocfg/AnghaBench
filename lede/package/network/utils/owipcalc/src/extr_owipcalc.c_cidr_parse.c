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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int* s6_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {TYPE_2__ v6; TYPE_1__ v4; } ;
struct cidr {int family; int prefix; TYPE_3__ addr; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 struct cidr* cidr_parse4 (char const*) ; 
 struct cidr* cidr_parse6 (char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*,char*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 struct cidr* malloc (int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strchr (char const*,char) ; 
 int strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cidr * cidr_parse(const char *op, const char *s, int af_hint)
{
	char *r;
	struct cidr *a;

	uint8_t i;
	uint32_t sum = strtoul(s, &r, 0);

	if ((r > s) && (*r == 0))
	{
		a = malloc(sizeof(struct cidr));

		if (!a)
			return NULL;

		if (af_hint == AF_INET)
		{
			a->family = AF_INET;
			a->prefix = sum;
			a->addr.v4.s_addr = htonl(sum);
		}
		else
		{
			a->family = AF_INET6;
			a->prefix = sum;

			for (i = 0; i <= 15; i++)
			{
				a->addr.v6.s6_addr[15-i] = sum % 256;
				sum >>= 8;
			}
		}

		return a;
	}

	if (strchr(s, ':'))
		a = cidr_parse6(s);
	else
		a = cidr_parse4(s);

	if (!a)
		return NULL;

	if (a->family != af_hint)
	{
		fprintf(stderr, "attempt to '%s' %s with %s address\n",
				op,
				(af_hint == AF_INET) ? "ipv4" : "ipv6",
				(af_hint != AF_INET) ? "ipv4" : "ipv6");
		exit(4);
	}

	return a;
}