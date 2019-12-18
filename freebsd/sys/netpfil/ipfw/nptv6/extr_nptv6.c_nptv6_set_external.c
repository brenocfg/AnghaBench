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
struct nptv6_cfg {int /*<<< orphan*/  flags; int /*<<< orphan*/  mask; struct in6_addr external; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN6_MASK_ADDR (struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NPTV6_READY ; 
 int /*<<< orphan*/  nptv6_calculate_adjustment (struct nptv6_cfg*) ; 

__attribute__((used)) static void
nptv6_set_external(struct nptv6_cfg *cfg, struct in6_addr *addr)
{

	cfg->external = *addr;
	IN6_MASK_ADDR(&cfg->external, &cfg->mask);
	nptv6_calculate_adjustment(cfg);
	cfg->flags |= NPTV6_READY;
}