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
struct ACPIRegionContent {int regtype; int /*<<< orphan*/  value; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  ACPI_PHYSICAL_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  RegionContentList ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ACPIRegionContent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 struct ACPIRegionContent* malloc (int) ; 

__attribute__((used)) static int
aml_simulate_regcontent_add(int regtype, ACPI_PHYSICAL_ADDRESS addr, UINT8 value)
{
	struct	ACPIRegionContent *rc;

	rc = malloc(sizeof(struct ACPIRegionContent));
	if (rc == NULL) {
		return (-1);	/* malloc fail */
	}
	rc->regtype = regtype;
	rc->addr = addr;
	rc->value = value;

	TAILQ_INSERT_TAIL(&RegionContentList, rc, links);
	return (0);
}