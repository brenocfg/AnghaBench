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
struct hast_snmp_resource {int dummy; } ;

/* Variables and functions */
 struct hast_snmp_resource* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct hast_snmp_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct hast_snmp_resource*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  resources ; 

__attribute__((used)) static void
free_resources(void)
{
	struct hast_snmp_resource *res;

	while ((res = TAILQ_FIRST(&resources)) != NULL) {
		TAILQ_REMOVE(&resources, res, link);
		free(res);
	}
}