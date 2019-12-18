#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  spa_guid; int /*<<< orphan*/  spa_vdevs; int /*<<< orphan*/ * spa_name; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_link ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  zfs_pools ; 

__attribute__((used)) static spa_t *
spa_create(uint64_t guid, const char *name)
{
	spa_t *spa;

	if ((spa = calloc(1, sizeof(spa_t))) == NULL)
		return (NULL);
	if ((spa->spa_name = strdup(name)) == NULL) {
		free(spa);
		return (NULL);
	}
	STAILQ_INIT(&spa->spa_vdevs);
	spa->spa_guid = guid;
	STAILQ_INSERT_TAIL(&zfs_pools, spa, spa_link);

	return (spa);
}