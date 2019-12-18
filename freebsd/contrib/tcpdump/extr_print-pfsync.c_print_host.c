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
typedef  scalar_t__ uint16_t ;
struct pf_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sa_family_t ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * inet_ntop (int /*<<< orphan*/ ,struct pf_addr*,char*,int) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 

__attribute__((used)) static void
print_host(netdissect_options *ndo, struct pf_addr *addr, uint16_t port,
    sa_family_t af, const char *proto)
{
	char buf[48];

	if (inet_ntop(af, addr, buf, sizeof(buf)) == NULL)
		ND_PRINT((ndo, "?"));
	else
		ND_PRINT((ndo, "%s", buf));

	if (port)
		ND_PRINT((ndo, ".%hu", ntohs(port)));
}