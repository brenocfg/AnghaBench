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
struct ACPIRegionContent {void* value; void* addr; void* regtype; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  aml_simulate_regcontent_write (void*,void*,void**) ; 
 int /*<<< orphan*/  aml_simulation_initialized ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 void* strtoq (char*,char**,int) ; 

__attribute__((used)) static void
aml_simulation_regload(const char *dumpfile)
{
	char	buf[256], *np, *ep;
	struct	ACPIRegionContent rc;
	FILE	*fp;

	if (!aml_simulation_initialized) {
		return;
	}

	if ((fp = fopen(dumpfile, "r")) == NULL) {
		return;
	}

	while (fgets(buf, sizeof buf, fp) != NULL) {
		np = buf;
		/* reading region type */
		rc.regtype = strtoq(np, &ep, 10);
		if (np == ep) {
			continue;
		}
		np = ep;

		/* reading address */
		rc.addr = strtoq(np, &ep, 16);
		if (np == ep) {
			continue;
		}
		np = ep;

		/* reading value */
		rc.value = strtoq(np, &ep, 16);
		if (np == ep) {
			continue;
		}
		aml_simulate_regcontent_write(rc.regtype, rc.addr, &rc.value);
	}

	fclose(fp);
}