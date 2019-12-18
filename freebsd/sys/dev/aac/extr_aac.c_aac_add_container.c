#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct aac_softc {int /*<<< orphan*/  aac_container_lock; int /*<<< orphan*/  aac_container_tqh; int /*<<< orphan*/  aac_dev; } ;
struct aac_mntobj {int dummy; } ;
struct aac_mntinforesp {scalar_t__ Status; TYPE_1__* MntTable; } ;
struct aac_container {int co_found; int /*<<< orphan*/  co_mntobj; int /*<<< orphan*/ * co_disk; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {scalar_t__ VolType; int /*<<< orphan*/  Capacity; int /*<<< orphan*/  FileSystemName; int /*<<< orphan*/  ObjectId; } ;

/* Variables and functions */
 scalar_t__ CT_NONE ; 
 char* HBA_FLAGS_DBG_INIT_B ; 
 int /*<<< orphan*/  M_AACBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ ST_OK ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct aac_container*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aac_container_types ; 
 int /*<<< orphan*/  aac_describe_code (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bcopy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  co_link ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct aac_container*) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
aac_add_container(struct aac_softc *sc, struct aac_mntinforesp *mir, int f)
{
	struct aac_container *co;
	device_t child;

	/*
	 * Check container volume type for validity.  Note that many of
	 * the possible types may never show up.
	 */
	if ((mir->Status == ST_OK) && (mir->MntTable[0].VolType != CT_NONE)) {
		co = (struct aac_container *)malloc(sizeof *co, M_AACBUF,
		       M_NOWAIT | M_ZERO);
		if (co == NULL)
			panic("Out of memory?!");
		fwprintf(sc, HBA_FLAGS_DBG_INIT_B, "id %x  name '%.16s'  size %u  type %d",
		      mir->MntTable[0].ObjectId,
		      mir->MntTable[0].FileSystemName,
		      mir->MntTable[0].Capacity, mir->MntTable[0].VolType);

		if ((child = device_add_child(sc->aac_dev, "aacd", -1)) == NULL)
			device_printf(sc->aac_dev, "device_add_child failed\n");
		else
			device_set_ivars(child, co);
		device_set_desc(child, aac_describe_code(aac_container_types,
				mir->MntTable[0].VolType));
		co->co_disk = child;
		co->co_found = f;
		bcopy(&mir->MntTable[0], &co->co_mntobj,
		      sizeof(struct aac_mntobj));
		mtx_lock(&sc->aac_container_lock);
		TAILQ_INSERT_TAIL(&sc->aac_container_tqh, co, co_link);
		mtx_unlock(&sc->aac_container_lock);
	}
}