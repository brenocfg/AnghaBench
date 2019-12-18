#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char const* uint16_t ;
struct servent {char const* s_name; } ;
struct protoent {int /*<<< orphan*/ * p_name; } ;
struct buf_pr {int dummy; } ;
struct TYPE_2__ {scalar_t__ do_resolv; } ;

/* Variables and functions */
 int IPPROTO_ETHERTYPE ; 
 int /*<<< orphan*/  bprintf (struct buf_pr*,char*,char const*) ; 
 TYPE_1__ co ; 
 int /*<<< orphan*/  ether_types ; 
 struct protoent* getprotobynumber (int) ; 
 struct servent* getservbyport (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htons (char const*) ; 
 char* match_value (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
print_port(struct buf_pr *bp, int proto, uint16_t port)
{

	if (proto == IPPROTO_ETHERTYPE) {
		char const *s;

		if (co.do_resolv && (s = match_value(ether_types, port)) )
			bprintf(bp, "%s", s);
		else
			bprintf(bp, "0x%04x", port);
	} else {
		struct servent *se = NULL;
		if (co.do_resolv) {
			struct protoent *pe = getprotobynumber(proto);

			se = getservbyport(htons(port), pe ? pe->p_name : NULL);
		}
		if (se)
			bprintf(bp, "%s", se->s_name);
		else
			bprintf(bp, "%d", port);
	}
}