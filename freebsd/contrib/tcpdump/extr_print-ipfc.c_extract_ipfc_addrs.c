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
struct ipfc_header {int /*<<< orphan*/ * ipfc_shost; int /*<<< orphan*/ * ipfc_dhost; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static inline void
extract_ipfc_addrs(const struct ipfc_header *ipfcp, char *ipfcsrc,
    char *ipfcdst)
{
	/*
	 * We assume that, as per RFC 2625, the lower 48 bits of the
	 * source and destination addresses are MAC addresses.
	 */
	memcpy(ipfcdst, (const char *)&ipfcp->ipfc_dhost[2], 6);
	memcpy(ipfcsrc, (const char *)&ipfcp->ipfc_shost[2], 6);
}