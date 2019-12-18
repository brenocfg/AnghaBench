#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_STRING ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * SYSCTL_ADD_ROOT_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _kern ; 
 int /*<<< orphan*/  a ; 
 int /*<<< orphan*/ * a_root ; 
 int /*<<< orphan*/ * a_root1 ; 
 int /*<<< orphan*/  b ; 
 int /*<<< orphan*/ * b_root ; 
 int /*<<< orphan*/  c ; 
 int /*<<< orphan*/  clist ; 
 int /*<<< orphan*/  clist1 ; 
 int /*<<< orphan*/  clist2 ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_dyn_sysctl_test ; 
 int /*<<< orphan*/  sysctl_remove_oid (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
load(module_t mod, int cmd, void *arg)
{
	int error;

	error = 0;
	switch (cmd) {
	case MOD_LOAD:
		/* Initialize the contexts */
		printf("Initializing contexts and creating subtrees.\n\n");
		sysctl_ctx_init(&clist);
		sysctl_ctx_init(&clist1);
		sysctl_ctx_init(&clist2);
		/*
		 * Create two partially overlapping subtrees, belonging
		 * to different contexts.
		 */
		printf("TREE		ROOT		  NAME\n");
		a_root = SYSCTL_ADD_ROOT_NODE(&clist,
			OID_AUTO, "dyn_sysctl", CTLFLAG_RW, 0,
			"dyn_sysctl root node");
		a_root = SYSCTL_ADD_ROOT_NODE(&clist1,
			OID_AUTO, "dyn_sysctl", CTLFLAG_RW, 0,
			"dyn_sysctl root node");
		if (a_root == NULL) {
			printf("SYSCTL_ADD_NODE failed!\n");
			return (EINVAL);
		}
		SYSCTL_ADD_LONG(&clist, SYSCTL_CHILDREN(a_root),
		    OID_AUTO, "long_a", CTLFLAG_RW, &a, "just to try");
		SYSCTL_ADD_INT(&clist, SYSCTL_CHILDREN(a_root),
		    OID_AUTO, "int_b", CTLFLAG_RW, &b, 0, "just to try 1");
		a_root1 = SYSCTL_ADD_NODE(&clist, SYSCTL_CHILDREN(a_root),
		    OID_AUTO, "nextlevel", CTLFLAG_RD, 0, "one level down");
		SYSCTL_ADD_STRING(&clist, SYSCTL_CHILDREN(a_root1),
		    OID_AUTO, "string_c", CTLFLAG_RD, c, 0, "just to try 2");
		printf("1. (%p)	/		  dyn_sysctl\n", &clist);

		/* Add a subtree under already existing category */
		a_root1 = SYSCTL_ADD_NODE(&clist, SYSCTL_STATIC_CHILDREN(_kern),
		    OID_AUTO, "dyn_sysctl", CTLFLAG_RW, 0, "dyn_sysctl root node");
		if (a_root1 == NULL) {
			printf("SYSCTL_ADD_NODE failed!\n");
			return (EINVAL);
		}
		SYSCTL_ADD_PROC(&clist, SYSCTL_CHILDREN(a_root1),
		    OID_AUTO, "procedure", CTLTYPE_STRING | CTLFLAG_RD,
		    NULL, 0, sysctl_dyn_sysctl_test, "A",
		    "I can be here, too");
		printf("   (%p)	/kern		  dyn_sysctl\n", &clist);

		/* Overlap second tree with the first. */
		b_root = SYSCTL_ADD_NODE(&clist1, SYSCTL_CHILDREN(a_root),
		    OID_AUTO, "nextlevel", CTLFLAG_RD, 0, "one level down");
		SYSCTL_ADD_STRING(&clist1, SYSCTL_CHILDREN(b_root),
		    OID_AUTO, "string_c1", CTLFLAG_RD, c, 0, "just to try 2");
		printf("2. (%p)	/		  dyn_sysctl	(overlapping #1)\n", &clist1);

		/*
		 * And now do something stupid. Connect another subtree to
		 * dynamic oid.
		 * WARNING: this is an example of WRONG use of dynamic sysctls.
		 */
		b_root=SYSCTL_ADD_NODE(&clist2, SYSCTL_CHILDREN(a_root1),
		    OID_AUTO, "bad", CTLFLAG_RW, 0, "dependent node");
		SYSCTL_ADD_STRING(&clist2, SYSCTL_CHILDREN(b_root),
		    OID_AUTO, "string_c", CTLFLAG_RD, c, 0, "shouldn't panic");
		printf("3. (%p)	/kern/dyn_sysctl  bad		(WRONG!)\n", &clist2);
		break;
	case MOD_UNLOAD:
		printf("1. Try to free ctx1 (%p): ", &clist);
		if (sysctl_ctx_free(&clist) != 0)
			printf("failed: expected. Need to remove ctx3 first.\n");
		else
			printf("HELP! sysctl_ctx_free(%p) succeeded. EXPECT PANIC!!!\n", &clist);
		printf("2. Try to free ctx3 (%p): ", &clist2);
		if (sysctl_ctx_free(&clist2) != 0) {
			printf("sysctl_ctx_free(%p) failed!\n", &clist2);
			/* Remove subtree forcefully... */
			sysctl_remove_oid(b_root, 1, 1);
			printf("sysctl_remove_oid(%p) succeeded\n", b_root);
		} else
			printf("Ok\n");
		printf("3. Try to free ctx1 (%p) again: ", &clist);
		if (sysctl_ctx_free(&clist) != 0) {
			printf("sysctl_ctx_free(%p) failed!\n", &clist);
			/* Remove subtree forcefully... */
			sysctl_remove_oid(a_root1, 1, 1);
			printf("sysctl_remove_oid(%p) succeeded\n", a_root1);
		} else
			printf("Ok\n");
		printf("4. Try to free ctx2 (%p): ", &clist1);
		if (sysctl_ctx_free(&clist1) != 0) {
			printf("sysctl_ctx_free(%p) failed!\n", &clist1);
			/* Remove subtree forcefully... */
			sysctl_remove_oid(a_root, 1, 1);
		} else
			printf("Ok\n");
		break;
	default:
		error = EOPNOTSUPP;
		break;
	}
	return (error);
}