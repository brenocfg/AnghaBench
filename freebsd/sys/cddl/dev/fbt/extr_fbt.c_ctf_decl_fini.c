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
struct TYPE_3__ {int /*<<< orphan*/ * cd_nodes; } ;
typedef  TYPE_1__ ctf_decl_t ;
typedef  int /*<<< orphan*/  ctf_decl_node_t ;

/* Variables and functions */
 int CTF_PREC_BASE ; 
 int CTF_PREC_MAX ; 
 int /*<<< orphan*/  M_FBT ; 
 int /*<<< orphan*/ * ctf_list_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctf_decl_fini(ctf_decl_t *cd)
{
	ctf_decl_node_t *cdp, *ndp;
	int i;

	for (i = CTF_PREC_BASE; i < CTF_PREC_MAX; i++) {
		for (cdp = ctf_list_next(&cd->cd_nodes[i]);
		    cdp != NULL; cdp = ndp) {
			ndp = ctf_list_next(cdp);
			free(cdp, M_FBT);
		}
	}
}