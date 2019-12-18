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
struct ciss_softc {int dummy; } ;
struct ciss_ldrive {TYPE_1__* cl_lstatus; } ;
struct TYPE_2__ {int status; int blocks_to_recover; int /*<<< orphan*/ * drive_failure_map; int /*<<< orphan*/  drive_rebuilding; } ;

/* Variables and functions */
 int CISS_BIG_MAP_BUS (struct ciss_softc*,int /*<<< orphan*/ ) ; 
 int CISS_BIG_MAP_ENTRIES ; 
 int CISS_BIG_MAP_TARGET (struct ciss_softc*,int /*<<< orphan*/ ) ; 
#define  CISS_LSTATUS_BECOMING_READY 137 
#define  CISS_LSTATUS_EXPANDING 136 
#define  CISS_LSTATUS_FAILED 135 
#define  CISS_LSTATUS_INTERIM_RECOVERY 134 
#define  CISS_LSTATUS_MISSING_PDRIVE 133 
#define  CISS_LSTATUS_OK 132 
#define  CISS_LSTATUS_QUEUED_FOR_EXPANSION 131 
#define  CISS_LSTATUS_READY_RECOVERY 130 
#define  CISS_LSTATUS_RECOVERING 129 
#define  CISS_LSTATUS_WRONG_PDRIVE 128 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ciss_print_ldrive(struct ciss_softc *sc, struct ciss_ldrive *ld)
{
    int		bus, target, i;

    if (ld->cl_lstatus == NULL) {
	printf("does not exist\n");
	return;
    }

    /* print drive status */
    switch(ld->cl_lstatus->status) {
    case CISS_LSTATUS_OK:
	printf("online\n");
	break;
    case CISS_LSTATUS_INTERIM_RECOVERY:
	printf("in interim recovery mode\n");
	break;
    case CISS_LSTATUS_READY_RECOVERY:
	printf("ready to begin recovery\n");
	break;
    case CISS_LSTATUS_RECOVERING:
	bus = CISS_BIG_MAP_BUS(sc, ld->cl_lstatus->drive_rebuilding);
	target = CISS_BIG_MAP_BUS(sc, ld->cl_lstatus->drive_rebuilding);
	printf("being recovered, working on physical drive %d.%d, %u blocks remaining\n",
	       bus, target, ld->cl_lstatus->blocks_to_recover);
	break;
    case CISS_LSTATUS_EXPANDING:
	printf("being expanded, %u blocks remaining\n",
	       ld->cl_lstatus->blocks_to_recover);
	break;
    case CISS_LSTATUS_QUEUED_FOR_EXPANSION:
	printf("queued for expansion\n");
	break;
    case CISS_LSTATUS_FAILED:
	printf("queued for expansion\n");
	break;
    case CISS_LSTATUS_WRONG_PDRIVE:
	printf("wrong physical drive inserted\n");
	break;
    case CISS_LSTATUS_MISSING_PDRIVE:
	printf("missing a needed physical drive\n");
	break;
    case CISS_LSTATUS_BECOMING_READY:
	printf("becoming ready\n");
	break;
    }

    /* print failed physical drives */
    for (i = 0; i < CISS_BIG_MAP_ENTRIES / 8; i++) {
	bus = CISS_BIG_MAP_BUS(sc, ld->cl_lstatus->drive_failure_map[i]);
	target = CISS_BIG_MAP_TARGET(sc, ld->cl_lstatus->drive_failure_map[i]);
	if (bus == -1)
	    continue;
	ciss_printf(sc, "physical drive %d:%d (%x) failed\n", bus, target,
		    ld->cl_lstatus->drive_failure_map[i]);
    }
}