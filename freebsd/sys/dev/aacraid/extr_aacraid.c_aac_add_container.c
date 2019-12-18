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
typedef  int /*<<< orphan*/  u_int32_t ;
struct aac_softc {int /*<<< orphan*/  aac_container_tqh; } ;
struct aac_mntobj {int dummy; } ;
struct aac_mntinforesp {scalar_t__ Status; TYPE_1__* MntTable; } ;
struct aac_container {int co_found; int /*<<< orphan*/  co_uid; int /*<<< orphan*/  co_mntobj; } ;
struct TYPE_2__ {scalar_t__ VolType; } ;

/* Variables and functions */
 scalar_t__ CT_NONE ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  M_AACRAIDBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ ST_OK ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct aac_container*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  co_link ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
aac_add_container(struct aac_softc *sc, struct aac_mntinforesp *mir, int f, 
		  u_int32_t uid)
{
	struct aac_container *co;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, ""); 

	/*
	 * Check container volume type for validity.  Note that many of
	 * the possible types may never show up.
	 */
	if ((mir->Status == ST_OK) && (mir->MntTable[0].VolType != CT_NONE)) {
		co = (struct aac_container *)malloc(sizeof *co, M_AACRAIDBUF,
		       M_NOWAIT | M_ZERO);
		if (co == NULL) {
			panic("Out of memory?!");
		}

		co->co_found = f;
		bcopy(&mir->MntTable[0], &co->co_mntobj,
		      sizeof(struct aac_mntobj));
		co->co_uid = uid;
		TAILQ_INSERT_TAIL(&sc->aac_container_tqh, co, co_link);
	}
}