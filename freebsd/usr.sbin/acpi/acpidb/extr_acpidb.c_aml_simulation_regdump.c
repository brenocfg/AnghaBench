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
typedef  int /*<<< orphan*/  uintmax_t ;
struct ACPIRegionContent {int regtype; int /*<<< orphan*/  value; scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  RegionContentList ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ACPIRegionContent* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ACPIRegionContent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aml_simulation_initialized ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ACPIRegionContent*) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static void
aml_simulation_regdump(const char *dumpfile)
{
	struct	ACPIRegionContent *rc;
	FILE	*fp;

	if (!aml_simulation_initialized) {
		return;
	}
	if ((fp = fopen(dumpfile, "w")) == NULL) {
		warn("%s", dumpfile);
		return;
	}
	while (!TAILQ_EMPTY(&RegionContentList)) {
		rc = TAILQ_FIRST(&RegionContentList);
		fprintf(fp, "%d	0x%jx	0x%x\n",
		    rc->regtype, (uintmax_t)rc->addr, rc->value);
		TAILQ_REMOVE(&RegionContentList, rc, links);
		free(rc);
	}

	fclose(fp);
	TAILQ_INIT(&RegionContentList);
}