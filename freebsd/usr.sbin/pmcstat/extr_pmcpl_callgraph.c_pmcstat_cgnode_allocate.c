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
typedef  int /*<<< orphan*/  uintfptr_t ;
struct pmcstat_image {int dummy; } ;
struct pmcstat_cgnode {int /*<<< orphan*/  pcg_children; scalar_t__ pcg_nchildren; scalar_t__ pcg_count; int /*<<< orphan*/  pcg_func; struct pmcstat_image* pcg_image; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 struct pmcstat_cgnode* malloc (int) ; 

__attribute__((used)) static struct pmcstat_cgnode *
pmcstat_cgnode_allocate(struct pmcstat_image *image, uintfptr_t pc)
{
	struct pmcstat_cgnode *cg;

	if ((cg = malloc(sizeof(*cg))) == NULL)
		err(EX_OSERR, "ERROR: Cannot allocate callgraph node");

	cg->pcg_image = image;
	cg->pcg_func = pc;

	cg->pcg_count = 0;
	cg->pcg_nchildren = 0;
	LIST_INIT(&cg->pcg_children);

	return (cg);
}