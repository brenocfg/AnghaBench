#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ ** spa_ddt; } ;
typedef  TYPE_1__ spa_t ;
typedef  enum ddt_type { ____Placeholder_ddt_type } ddt_type ;
typedef  enum ddt_class { ____Placeholder_ddt_class } ddt_class ;
typedef  int /*<<< orphan*/  ddt_t ;
struct TYPE_6__ {int /*<<< orphan*/  dde_key; } ;
typedef  TYPE_2__ ddt_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 size_t BP_GET_CHECKSUM (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BP_GET_DEDUP (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int DDT_CLASS_UNIQUE ; 
 int DDT_TYPES ; 
 int /*<<< orphan*/  ddt_key_fill (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ ddt_object_lookup (int /*<<< orphan*/ *,int,int,TYPE_2__*) ; 

boolean_t
ddt_class_contains(spa_t *spa, enum ddt_class max_class, const blkptr_t *bp)
{
	ddt_t *ddt;
	ddt_entry_t dde;

	if (!BP_GET_DEDUP(bp))
		return (B_FALSE);

	if (max_class == DDT_CLASS_UNIQUE)
		return (B_TRUE);

	ddt = spa->spa_ddt[BP_GET_CHECKSUM(bp)];

	ddt_key_fill(&dde.dde_key, bp);

	for (enum ddt_type type = 0; type < DDT_TYPES; type++)
		for (enum ddt_class class = 0; class <= max_class; class++)
			if (ddt_object_lookup(ddt, type, class, &dde) == 0)
				return (B_TRUE);

	return (B_FALSE);
}