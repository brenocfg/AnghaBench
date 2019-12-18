#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  spa_meta_objset; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_8__ {scalar_t__ db_data; } ;
typedef  TYPE_2__ dmu_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_ENCODE_XDR ; 
 size_t P2ROUNDUP (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_CONFIG_BLOCKSIZE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (char*,size_t) ; 
 scalar_t__ dmu_bonus_hold (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  dmu_buf_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_write (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t,char*,int /*<<< orphan*/ *) ; 
 char* kmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,size_t) ; 
 scalar_t__ nvlist_pack (int /*<<< orphan*/ *,char**,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_size (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_sync_nvlist(spa_t *spa, uint64_t obj, nvlist_t *nv, dmu_tx_t *tx)
{
	char *packed = NULL;
	size_t bufsize;
	size_t nvsize = 0;
	dmu_buf_t *db;

	VERIFY(nvlist_size(nv, &nvsize, NV_ENCODE_XDR) == 0);

	/*
	 * Write full (SPA_CONFIG_BLOCKSIZE) blocks of configuration
	 * information.  This avoids the dmu_buf_will_dirty() path and
	 * saves us a pre-read to get data we don't actually care about.
	 */
	bufsize = P2ROUNDUP((uint64_t)nvsize, SPA_CONFIG_BLOCKSIZE);
	packed = kmem_alloc(bufsize, KM_SLEEP);

	VERIFY(nvlist_pack(nv, &packed, &nvsize, NV_ENCODE_XDR,
	    KM_SLEEP) == 0);
	bzero(packed + nvsize, bufsize - nvsize);

	dmu_write(spa->spa_meta_objset, obj, 0, bufsize, packed, tx);

	kmem_free(packed, bufsize);

	VERIFY(0 == dmu_bonus_hold(spa->spa_meta_objset, obj, FTAG, &db));
	dmu_buf_will_dirty(db, tx);
	*(uint64_t *)db->db_data = nvsize;
	dmu_buf_rele(db, FTAG);
}