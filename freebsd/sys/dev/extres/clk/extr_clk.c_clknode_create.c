#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid {int dummy; } ;
struct clknode_init_def {char* name; int flags; int parent_cnt; int /*<<< orphan*/  id; int /*<<< orphan*/  parent_names; } ;
struct clknode {int flags; char* name; int parent_cnt; int /*<<< orphan*/  enable_cnt; int /*<<< orphan*/  sysctl_ctx; int /*<<< orphan*/  freq; int /*<<< orphan*/  parent_idx; int /*<<< orphan*/ * parent; struct clkdom* clkdom; int /*<<< orphan*/  id; int /*<<< orphan*/  parent_names; void* parents; void* softc; int /*<<< orphan*/  children; int /*<<< orphan*/  lock; } ;
struct clkdom {int /*<<< orphan*/  clknode_list; } ;
typedef  int /*<<< orphan*/  kobj_t ;
typedef  int /*<<< orphan*/  kobj_class_t ;
typedef  TYPE_1__* clknode_class_t ;
struct TYPE_3__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKNODE_IDX_NONE ; 
 int /*<<< orphan*/  CLKNODE_SYSCTL_CHILDREN_LIST ; 
 int /*<<< orphan*/  CLKNODE_SYSCTL_PARENT ; 
 int /*<<< orphan*/  CLKNODE_SYSCTL_PARENTS_LIST ; 
 int CLK_NODE_LINKED ; 
 int CLK_NODE_STATIC_STRINGS ; 
 int /*<<< orphan*/  CLK_TOPO_SLOCK () ; 
 int /*<<< orphan*/  CLK_TOPO_UNLOCK () ; 
 int CTLFLAG_RD ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_CLOCK ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct clknode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_U64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct clknode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hw_clock ; 
 int /*<<< orphan*/  clkdom_link ; 
 int /*<<< orphan*/  clklist_link ; 
 struct clknode* clknode_find_by_name (char*) ; 
 int /*<<< orphan*/  clknode_list ; 
 int /*<<< orphan*/  clknode_sysctl ; 
 int /*<<< orphan*/  kobj_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,char*) ; 
 char* strdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup_list (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 

struct clknode *
clknode_create(struct clkdom * clkdom, clknode_class_t clknode_class,
    const struct clknode_init_def *def)
{
	struct clknode *clknode;
	struct sysctl_oid *clknode_oid;
	bool replaced;

	KASSERT(def->name != NULL, ("clock name is NULL"));
	KASSERT(def->name[0] != '\0', ("clock name is empty"));
	if (def->flags & CLK_NODE_LINKED) {
		KASSERT(def->parent_cnt == 0,
		 ("Linked clock must not have parents"));
		KASSERT(clknode_class->size== 0,
		 ("Linked clock cannot have own softc"));
	}

	/* Process duplicated clocks */
	CLK_TOPO_SLOCK();
	clknode = clknode_find_by_name(def->name);
	CLK_TOPO_UNLOCK();
		if (clknode !=  NULL) {
		if (!(clknode->flags & CLK_NODE_LINKED) &&
		    def->flags & CLK_NODE_LINKED) {
			/*
			 * New clock is linked and real already exists.
			 * Do nothing and return real node. It is in right
			 * domain, enqueued in right lists and fully initialized.
			 */
			return (clknode);
		} else if (clknode->flags & CLK_NODE_LINKED &&
		   !(def->flags & CLK_NODE_LINKED)) {
			/*
			 * New clock is real but linked already exists.
			 * Remove old linked node from originating domain
			 * (real clock must be owned by another) and from
			 * global names link (it will be added back into it
			 * again in following clknode_register()). Then reuse
			 * original clknode structure and reinitialize it
			 * with new dat. By this, all lists containing this
			 * node remains valid, but the new node virtually
			 * replace the linked one.
			 */
			KASSERT(clkdom != clknode->clkdom,
			    ("linked clock must be from another "
			    "domain that real one"));
			TAILQ_REMOVE(&clkdom->clknode_list, clknode,
			    clkdom_link);
			TAILQ_REMOVE(&clknode_list, clknode, clklist_link);
			replaced = true;
		} else if (clknode->flags & CLK_NODE_LINKED &&
		   def->flags & CLK_NODE_LINKED) {
			/*
			 * Both clocks are linked.
			 * Return old one, so we hold only one copy od link.
			 */
			return (clknode);
		} else {
			/* Both clocks are real */
			panic("Duplicated clock registration: %s\n", def->name);
		}
	} else {
		/* Create clknode object and initialize it. */
		clknode = malloc(sizeof(struct clknode), M_CLOCK,
		    M_WAITOK | M_ZERO);
		sx_init(&clknode->lock, "Clocknode lock");
		TAILQ_INIT(&clknode->children);
		replaced = false;
	}

	kobj_init((kobj_t)clknode, (kobj_class_t)clknode_class);

	/* Allocate softc if required. */
	if (clknode_class->size > 0) {
		clknode->softc = malloc(clknode_class->size,
		    M_CLOCK, M_WAITOK | M_ZERO);
	}

	/* Prepare array for ptrs to parent clocks. */
	clknode->parents = malloc(sizeof(struct clknode *) * def->parent_cnt,
	    M_CLOCK, M_WAITOK | M_ZERO);

	/* Copy all strings unless they're flagged as static. */
	if (def->flags & CLK_NODE_STATIC_STRINGS) {
		clknode->name = def->name;
		clknode->parent_names = def->parent_names;
	} else {
		clknode->name = strdup(def->name, M_CLOCK);
		clknode->parent_names =
		    strdup_list(def->parent_names, def->parent_cnt);
	}

	/* Rest of init. */
	clknode->id = def->id;
	clknode->clkdom = clkdom;
	clknode->flags = def->flags;
	clknode->parent_cnt = def->parent_cnt;
	clknode->parent = NULL;
	clknode->parent_idx = CLKNODE_IDX_NONE;

	if (replaced)
			return (clknode);

	sysctl_ctx_init(&clknode->sysctl_ctx);
	clknode_oid = SYSCTL_ADD_NODE(&clknode->sysctl_ctx,
	    SYSCTL_STATIC_CHILDREN(_hw_clock),
	    OID_AUTO, clknode->name,
	    CTLFLAG_RD, 0, "A clock node");

	SYSCTL_ADD_U64(&clknode->sysctl_ctx,
	    SYSCTL_CHILDREN(clknode_oid),
	    OID_AUTO, "frequency",
	    CTLFLAG_RD, &clknode->freq, 0, "The clock frequency");
	SYSCTL_ADD_PROC(&clknode->sysctl_ctx,
	    SYSCTL_CHILDREN(clknode_oid),
	    OID_AUTO, "parent",
	    CTLTYPE_STRING | CTLFLAG_RD,
	    clknode, CLKNODE_SYSCTL_PARENT, clknode_sysctl,
	    "A",
	    "The clock parent");
	SYSCTL_ADD_PROC(&clknode->sysctl_ctx,
	    SYSCTL_CHILDREN(clknode_oid),
	    OID_AUTO, "parents",
	    CTLTYPE_STRING | CTLFLAG_RD,
	    clknode, CLKNODE_SYSCTL_PARENTS_LIST, clknode_sysctl,
	    "A",
	    "The clock parents list");
	SYSCTL_ADD_PROC(&clknode->sysctl_ctx,
	    SYSCTL_CHILDREN(clknode_oid),
	    OID_AUTO, "childrens",
	    CTLTYPE_STRING | CTLFLAG_RD,
	    clknode, CLKNODE_SYSCTL_CHILDREN_LIST, clknode_sysctl,
	    "A",
	    "The clock childrens list");
	SYSCTL_ADD_INT(&clknode->sysctl_ctx,
	    SYSCTL_CHILDREN(clknode_oid),
	    OID_AUTO, "enable_cnt",
	    CTLFLAG_RD, &clknode->enable_cnt, 0, "The clock enable counter");

	return (clknode);
}