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
struct ether_addr {int dummy; } ;

/* Variables and functions */
 struct ether_addr* ether_aton (char const*) ; 
 scalar_t__ ether_hostton (char const*,struct ether_addr*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
get_ether(char const *text, struct ether_addr *addr)
{
	struct ether_addr *paddr;

	paddr = ether_aton(text);
	if (paddr != NULL) {
		*addr = *paddr;
		return (0);
	}
	if (ether_hostton(text, addr)) {
		warnx("no match for host %s found", text);
		return (-1);
	}
	return (0);
}