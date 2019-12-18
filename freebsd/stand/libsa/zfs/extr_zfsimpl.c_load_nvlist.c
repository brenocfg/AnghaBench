#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  spa_mos; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_10__ {scalar_t__ dn_type; scalar_t__ dn_bonustype; int dn_bonuslen; } ;
typedef  TYPE_2__ dnode_phys_t ;

/* Variables and functions */
 scalar_t__ DMU_OT_PACKED_NVLIST ; 
 scalar_t__ DMU_OT_PACKED_NVLIST_SIZE ; 
 scalar_t__ DN_BONUS (TYPE_2__*) ; 
 int EIO ; 
 int ENOMEM ; 
 int dnode_read (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (size_t) ; 
 int objset_get_dnode (TYPE_1__*,int /*<<< orphan*/ *,size_t,TYPE_2__*) ; 

__attribute__((used)) static int
load_nvlist(spa_t *spa, uint64_t obj, unsigned char **value)
{
	dnode_phys_t dir;
	size_t size;
	int rc;
	unsigned char *nv;

	*value = NULL;
	if ((rc = objset_get_dnode(spa, &spa->spa_mos, obj, &dir)) != 0)
		return (rc);
	if (dir.dn_type != DMU_OT_PACKED_NVLIST &&
	    dir.dn_bonustype != DMU_OT_PACKED_NVLIST_SIZE) {
		return (EIO);
	}

	if (dir.dn_bonuslen != sizeof (uint64_t))
		return (EIO);

	size = *(uint64_t *)DN_BONUS(&dir);
	nv = malloc(size);
	if (nv == NULL)
		return (ENOMEM);

	rc = dnode_read(spa, &dir, 0, nv, size);
	if (rc != 0) {
		free(nv);
		nv = NULL;
		return (rc);
	}
	*value = nv;
	return (rc);
}