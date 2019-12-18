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
struct libalias {int dummy; } ;
struct alias_data {int /*<<< orphan*/ * sport; int /*<<< orphan*/ * dport; int /*<<< orphan*/ * aport; int /*<<< orphan*/ * aaddr; int /*<<< orphan*/ * lnk; } ;

/* Variables and functions */
 scalar_t__ NETBIOS_NS_PORT_NUMBER ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fingerprint2(struct libalias *la, struct alias_data *ah)
{

	if (ah->dport == NULL || ah->sport == NULL || ah->lnk == NULL ||
	    ah->aaddr == NULL || ah->aport == NULL)
		return (-1);
	if (ntohs(*ah->dport) == NETBIOS_NS_PORT_NUMBER
	    || ntohs(*ah->sport) == NETBIOS_NS_PORT_NUMBER)
		return (0);
	return (-1);
}