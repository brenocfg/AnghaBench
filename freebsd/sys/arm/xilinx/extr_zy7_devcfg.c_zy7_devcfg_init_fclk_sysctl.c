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
struct zy7_devcfg_softc {int /*<<< orphan*/  sysctl_tree; struct sysctl_oid* sysctl_tree_top; } ;
struct sysctl_oid {int dummy; } ;
typedef  int /*<<< orphan*/  fclk_num ;
struct TYPE_3__ {int /*<<< orphan*/  actual_frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int CTLTYPE_STRING ; 
 int FCLK_NUM ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 void* SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,TYPE_1__*,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hw_fpga ; 
 TYPE_1__* fclk_configs ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zy7_devcfg_fclk_sysctl_freq ; 
 int /*<<< orphan*/  zy7_devcfg_fclk_sysctl_source ; 

__attribute__((used)) static int
zy7_devcfg_init_fclk_sysctl(struct zy7_devcfg_softc *sc)
{
	struct sysctl_oid *fclk_node;
	char fclk_num[4];
	int i;

	sysctl_ctx_init(&sc->sysctl_tree);
	sc->sysctl_tree_top = SYSCTL_ADD_NODE(&sc->sysctl_tree,
	    SYSCTL_STATIC_CHILDREN(_hw_fpga), OID_AUTO, "fclk",
	    CTLFLAG_RD, 0, "");
	if (sc->sysctl_tree_top == NULL) {
		sysctl_ctx_free(&sc->sysctl_tree);
		return (-1);
	}

	for (i = 0; i < FCLK_NUM; i++) {
		snprintf(fclk_num, sizeof(fclk_num), "%d", i);
		fclk_node = SYSCTL_ADD_NODE(&sc->sysctl_tree,
		    SYSCTL_CHILDREN(sc->sysctl_tree_top), OID_AUTO, fclk_num,
		    CTLFLAG_RD, 0, "");

		SYSCTL_ADD_INT(&sc->sysctl_tree,
		    SYSCTL_CHILDREN(fclk_node), OID_AUTO,
		    "actual_freq", CTLFLAG_RD, 
		    &fclk_configs[i].actual_frequency, i,
		    "Actual frequency");
		SYSCTL_ADD_PROC(&sc->sysctl_tree,
		    SYSCTL_CHILDREN(fclk_node), OID_AUTO,
		    "freq", CTLFLAG_RW | CTLTYPE_INT, 
		    &fclk_configs[i], i,
		    zy7_devcfg_fclk_sysctl_freq,
		    "I", "Configured frequency");
		SYSCTL_ADD_PROC(&sc->sysctl_tree,
		    SYSCTL_CHILDREN(fclk_node), OID_AUTO,
		    "source", CTLFLAG_RW | CTLTYPE_STRING, 
		    &fclk_configs[i], i, 
		    zy7_devcfg_fclk_sysctl_source,
		    "A", "Clock source");
	}

	return (0);
}