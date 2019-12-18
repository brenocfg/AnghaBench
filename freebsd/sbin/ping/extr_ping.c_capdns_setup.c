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
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int AF_INET ; 
 int /*<<< orphan*/  cap_close (int /*<<< orphan*/ *) ; 
 scalar_t__ cap_dns_family_limit (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ cap_dns_type_limit (int /*<<< orphan*/ *,char const**,int) ; 
 int /*<<< orphan*/ * cap_init () ; 
 int /*<<< orphan*/ * cap_service_open (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 

__attribute__((used)) static cap_channel_t *
capdns_setup(void)
{
	cap_channel_t *capcas, *capdnsloc;
#ifdef WITH_CASPER
	const char *types[2];
	int families[1];
#endif
	capcas = cap_init();
	if (capcas == NULL)
		err(1, "unable to create casper process");
	capdnsloc = cap_service_open(capcas, "system.dns");
	/* Casper capability no longer needed. */
	cap_close(capcas);
	if (capdnsloc == NULL)
		err(1, "unable to open system.dns service");
#ifdef WITH_CASPER
	types[0] = "NAME2ADDR";
	types[1] = "ADDR2NAME";
	if (cap_dns_type_limit(capdnsloc, types, 2) < 0)
		err(1, "unable to limit access to system.dns service");
	families[0] = AF_INET;
	if (cap_dns_family_limit(capdnsloc, families, 1) < 0)
		err(1, "unable to limit access to system.dns service");
#endif
	return (capdnsloc);
}