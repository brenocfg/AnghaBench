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
struct TYPE_6__ {int vim_havecounts; scalar_t__ dn_bonuslen; struct TYPE_6__* vim_dn; int /*<<< orphan*/ * vim_entries; int /*<<< orphan*/  vim_object; int /*<<< orphan*/ * vim_objset; int /*<<< orphan*/ * vim_phys; int /*<<< orphan*/ * vim_spa; } ;
typedef  TYPE_1__ vdev_indirect_mapping_t ;
typedef  int /*<<< orphan*/  vdev_indirect_mapping_phys_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  objset_phys_t ;

/* Variables and functions */
 scalar_t__ DN_BONUS (TYPE_1__*) ; 
 scalar_t__ VDEV_INDIRECT_MAPPING_SIZE_V0 ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int objset_get_dnode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

vdev_indirect_mapping_t *
vdev_indirect_mapping_open(spa_t *spa, objset_phys_t *os,
    uint64_t mapping_object)
{
	vdev_indirect_mapping_t *vim;
	vdev_indirect_mapping_phys_t *vim_phys;
	int rc;

	vim = calloc(1, sizeof (*vim));
	if (vim == NULL)
		return (NULL);

	vim->vim_dn = calloc(1, sizeof (*vim->vim_dn));
	if (vim->vim_dn == NULL) {
		free(vim);
		return (NULL);
	}

	rc = objset_get_dnode(spa, os, mapping_object, vim->vim_dn);
	if (rc != 0) {
		free(vim->vim_dn);
		free(vim);
		return (NULL);
	}

	vim->vim_spa = spa;
	vim->vim_phys = malloc(sizeof (*vim->vim_phys));
	if (vim->vim_phys == NULL) {
		free(vim->vim_dn);
		free(vim);
		return (NULL);
	}

	vim_phys = (vdev_indirect_mapping_phys_t *)DN_BONUS(vim->vim_dn);
	*vim->vim_phys = *vim_phys;

	vim->vim_objset = os;
	vim->vim_object = mapping_object;
	vim->vim_entries = NULL;

	vim->vim_havecounts =
	    (vim->vim_dn->dn_bonuslen > VDEV_INDIRECT_MAPPING_SIZE_V0);
	return (vim);
}