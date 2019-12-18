#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct sysctl_oid {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  always_on; int /*<<< orphan*/  boot_on; int /*<<< orphan*/  enable_delay; int /*<<< orphan*/  ramp_delay; int /*<<< orphan*/  max_uamp; int /*<<< orphan*/  min_uamp; int /*<<< orphan*/  max_uvolt; int /*<<< orphan*/  min_uvolt; } ;
struct regnode_init_def {char* name; int flags; char* parent_name; int /*<<< orphan*/  ofw_node; TYPE_1__ std_param; int /*<<< orphan*/  id; } ;
struct regnode {char* name; char* parent_name; int flags; int /*<<< orphan*/  sysctl_ctx; TYPE_1__ std_param; int /*<<< orphan*/  enable_cnt; int /*<<< orphan*/  ofw_node; int /*<<< orphan*/ * parent; int /*<<< orphan*/  pdev; int /*<<< orphan*/  id; int /*<<< orphan*/  consumers_list; void* softc; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__* regnode_class_t ;
typedef  int /*<<< orphan*/  kobj_t ;
typedef  int /*<<< orphan*/  kobj_class_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int size; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_REGULATOR ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int REGULATOR_FLAGS_STATIC ; 
 int /*<<< orphan*/  REG_TOPO_SLOCK () ; 
 int /*<<< orphan*/  REG_TOPO_UNLOCK () ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct regnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_U8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _hw_regulator ; 
 int /*<<< orphan*/  kobj_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,char*) ; 
 int /*<<< orphan*/ * regnode_find_by_name (char*) ; 
 int /*<<< orphan*/  regnode_uvolt_sysctl ; 
 void* strdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 

struct regnode *
regnode_create(device_t pdev, regnode_class_t regnode_class,
    struct regnode_init_def *def)
{
	struct regnode *regnode;
	struct sysctl_oid *regnode_oid;

	KASSERT(def->name != NULL, ("regulator name is NULL"));
	KASSERT(def->name[0] != '\0', ("regulator name is empty"));

	REG_TOPO_SLOCK();
	if (regnode_find_by_name(def->name) != NULL)
		panic("Duplicated regulator registration: %s\n", def->name);
	REG_TOPO_UNLOCK();

	/* Create object and initialize it. */
	regnode = malloc(sizeof(struct regnode), M_REGULATOR,
	    M_WAITOK | M_ZERO);
	kobj_init((kobj_t)regnode, (kobj_class_t)regnode_class);
	sx_init(&regnode->lock, "Regulator node lock");

	/* Allocate softc if required. */
	if (regnode_class->size > 0) {
		regnode->softc = malloc(regnode_class->size, M_REGULATOR,
		    M_WAITOK | M_ZERO);
	}


	/* Copy all strings unless they're flagged as static. */
	if (def->flags & REGULATOR_FLAGS_STATIC) {
		regnode->name = def->name;
		regnode->parent_name = def->parent_name;
	} else {
		regnode->name = strdup(def->name, M_REGULATOR);
		if (def->parent_name != NULL)
			regnode->parent_name = strdup(def->parent_name,
			    M_REGULATOR);
	}

	/* Rest of init. */
	TAILQ_INIT(&regnode->consumers_list);
	regnode->id = def->id;
	regnode->pdev = pdev;
	regnode->flags = def->flags;
	regnode->parent = NULL;
	regnode->std_param = def->std_param;
#ifdef FDT
	regnode->ofw_node = def->ofw_node;
#endif

	sysctl_ctx_init(&regnode->sysctl_ctx);
	regnode_oid = SYSCTL_ADD_NODE(&regnode->sysctl_ctx,
	    SYSCTL_STATIC_CHILDREN(_hw_regulator),
	    OID_AUTO, regnode->name,
	    CTLFLAG_RD, 0, "A regulator node");

	SYSCTL_ADD_INT(&regnode->sysctl_ctx,
	    SYSCTL_CHILDREN(regnode_oid),
	    OID_AUTO, "min_uvolt",
	    CTLFLAG_RD, &regnode->std_param.min_uvolt, 0,
	    "Minimal voltage (in uV)");
	SYSCTL_ADD_INT(&regnode->sysctl_ctx,
	    SYSCTL_CHILDREN(regnode_oid),
	    OID_AUTO, "max_uvolt",
	    CTLFLAG_RD, &regnode->std_param.max_uvolt, 0,
	    "Maximal voltage (in uV)");
	SYSCTL_ADD_INT(&regnode->sysctl_ctx,
	    SYSCTL_CHILDREN(regnode_oid),
	    OID_AUTO, "min_uamp",
	    CTLFLAG_RD, &regnode->std_param.min_uamp, 0,
	    "Minimal amperage (in uA)");
	SYSCTL_ADD_INT(&regnode->sysctl_ctx,
	    SYSCTL_CHILDREN(regnode_oid),
	    OID_AUTO, "max_uamp",
	    CTLFLAG_RD, &regnode->std_param.max_uamp, 0,
	    "Maximal amperage (in uA)");
	SYSCTL_ADD_INT(&regnode->sysctl_ctx,
	    SYSCTL_CHILDREN(regnode_oid),
	    OID_AUTO, "ramp_delay",
	    CTLFLAG_RD, &regnode->std_param.ramp_delay, 0,
	    "Ramp delay (in uV/us)");
	SYSCTL_ADD_INT(&regnode->sysctl_ctx,
	    SYSCTL_CHILDREN(regnode_oid),
	    OID_AUTO, "enable_delay",
	    CTLFLAG_RD, &regnode->std_param.enable_delay, 0,
	    "Enable delay (in us)");
	SYSCTL_ADD_INT(&regnode->sysctl_ctx,
	    SYSCTL_CHILDREN(regnode_oid),
	    OID_AUTO, "enable_cnt",
	    CTLFLAG_RD, &regnode->enable_cnt, 0,
	    "The regulator enable counter");
	SYSCTL_ADD_U8(&regnode->sysctl_ctx,
	    SYSCTL_CHILDREN(regnode_oid),
	    OID_AUTO, "boot_on",
	    CTLFLAG_RD, (uint8_t *) &regnode->std_param.boot_on, 0,
	    "Is enabled on boot");
	SYSCTL_ADD_U8(&regnode->sysctl_ctx,
	    SYSCTL_CHILDREN(regnode_oid),
	    OID_AUTO, "always_on",
	    CTLFLAG_RD, (uint8_t *)&regnode->std_param.always_on, 0,
	    "Is always enabled");

	SYSCTL_ADD_PROC(&regnode->sysctl_ctx,
	    SYSCTL_CHILDREN(regnode_oid),
	    OID_AUTO, "uvolt",
	    CTLTYPE_INT | CTLFLAG_RD,
	    regnode, 0, regnode_uvolt_sysctl,
	    "I",
	    "Current voltage (in uV)");

	return (regnode);
}