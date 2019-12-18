#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  spa_meta_objset; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_7__ {scalar_t__ db_data; } ;
typedef  TYPE_2__ dmu_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_READ_PREFETCH ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int dmu_bonus_hold (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  dmu_buf_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int dmu_read (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t,char*,int /*<<< orphan*/ ) ; 
 char* kmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,size_t) ; 
 int nvlist_unpack (char*,size_t,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
load_nvlist(spa_t *spa, uint64_t obj, nvlist_t **value)
{
	dmu_buf_t *db;
	char *packed = NULL;
	size_t nvsize = 0;
	int error;
	*value = NULL;

	error = dmu_bonus_hold(spa->spa_meta_objset, obj, FTAG, &db);
	if (error != 0)
		return (error);

	nvsize = *(uint64_t *)db->db_data;
	dmu_buf_rele(db, FTAG);

	packed = kmem_alloc(nvsize, KM_SLEEP);
	error = dmu_read(spa->spa_meta_objset, obj, 0, nvsize, packed,
	    DMU_READ_PREFETCH);
	if (error == 0)
		error = nvlist_unpack(packed, nvsize, value, 0);
	kmem_free(packed, nvsize);

	return (error);
}