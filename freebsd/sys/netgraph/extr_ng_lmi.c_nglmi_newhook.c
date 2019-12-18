#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  void* hook_p ;
struct TYPE_7__ {int flags; int protoID; void* lmi_channel0; void* protoname; void* lmi_channel1023; void* lmi_group4; void* lmi_annexD; void* lmi_annexA; } ;

/* Variables and functions */
 int EINVAL ; 
 void* NAME_ANNEXA ; 
 void* NAME_ANNEXD ; 
 void* NAME_GROUP4 ; 
 void* NAME_NONE ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (void*,TYPE_1__*) ; 
 int /*<<< orphan*/  NG_LMI_HOOK_ANNEXA ; 
 int /*<<< orphan*/  NG_LMI_HOOK_ANNEXD ; 
 int /*<<< orphan*/  NG_LMI_HOOK_AUTO0 ; 
 int /*<<< orphan*/  NG_LMI_HOOK_AUTO1023 ; 
 int /*<<< orphan*/  NG_LMI_HOOK_DEBUG ; 
 int /*<<< orphan*/  NG_LMI_HOOK_GROUPOF4 ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCF_ANNEX_A ; 
 int /*<<< orphan*/  SCF_ANNEX_D ; 
 int SCF_CONNECTED ; 
 int /*<<< orphan*/  SCF_GROUP4 ; 
 int /*<<< orphan*/  SETLMITYPE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nglmi_startup_auto (TYPE_1__*) ; 
 int /*<<< orphan*/  nglmi_startup_fixed (TYPE_1__*,void*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nglmi_newhook(node_p node, hook_p hook, const char *name)
{
	sc_p sc = NG_NODE_PRIVATE(node);

	if (strcmp(name, NG_LMI_HOOK_DEBUG) == 0) {
		NG_HOOK_SET_PRIVATE(hook, NULL);
		return (0);
	}
	if (sc->flags & SCF_CONNECTED) {
		/* already connected, return an error */
		return (EINVAL);
	}
	if (strcmp(name, NG_LMI_HOOK_ANNEXA) == 0) {
		sc->lmi_annexA = hook;
		NG_HOOK_SET_PRIVATE(hook, NG_NODE_PRIVATE(node));
		sc->protoID = 8;
		SETLMITYPE(sc, SCF_ANNEX_A);
		sc->protoname = NAME_ANNEXA;
		nglmi_startup_fixed(sc, hook);
	} else if (strcmp(name, NG_LMI_HOOK_ANNEXD) == 0) {
		sc->lmi_annexD = hook;
		NG_HOOK_SET_PRIVATE(hook, NG_NODE_PRIVATE(node));
		sc->protoID = 8;
		SETLMITYPE(sc, SCF_ANNEX_D);
		sc->protoname = NAME_ANNEXD;
		nglmi_startup_fixed(sc, hook);
	} else if (strcmp(name, NG_LMI_HOOK_GROUPOF4) == 0) {
		sc->lmi_group4 = hook;
		NG_HOOK_SET_PRIVATE(hook, NG_NODE_PRIVATE(node));
		sc->protoID = 9;
		SETLMITYPE(sc, SCF_GROUP4);
		sc->protoname = NAME_GROUP4;
		nglmi_startup_fixed(sc, hook);
	} else if (strcmp(name, NG_LMI_HOOK_AUTO0) == 0) {
		/* Note this, and if B is already installed, we're complete */
		sc->lmi_channel0 = hook;
		sc->protoname = NAME_NONE;
		NG_HOOK_SET_PRIVATE(hook, NG_NODE_PRIVATE(node));
		if (sc->lmi_channel1023)
			nglmi_startup_auto(sc);
	} else if (strcmp(name, NG_LMI_HOOK_AUTO1023) == 0) {
		/* Note this, and if A is already installed, we're complete */
		sc->lmi_channel1023 = hook;
		sc->protoname = NAME_NONE;
		NG_HOOK_SET_PRIVATE(hook, NG_NODE_PRIVATE(node));
		if (sc->lmi_channel0)
			nglmi_startup_auto(sc);
	} else
		return (EINVAL);		/* unknown hook */
	return (0);
}