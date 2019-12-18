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
struct bhnd_pmu_query {int dummy; } ;
struct bcm_platform {struct bhnd_pmu_query pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_has_pmu (struct bcm_platform*) ; 

__attribute__((used)) static struct bhnd_pmu_query *
bcm_get_pmu(struct bcm_platform	*bp)
{
	if (!bcm_has_pmu(bp))
		return (NULL);
	return (&bp->pmu);
}