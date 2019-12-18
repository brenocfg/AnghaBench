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
struct pnpinfo {struct pnpinfo* pi_argv; struct pnpinfo* pi_module; struct pnpinfo* pi_desc; struct pnpinfo* id_ident; int /*<<< orphan*/  pi_ident; } ;
struct pnpident {struct pnpident* pi_argv; struct pnpident* pi_module; struct pnpident* pi_desc; struct pnpident* id_ident; int /*<<< orphan*/  pi_ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct pnpinfo* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct pnpinfo*) ; 
 int /*<<< orphan*/  id_link ; 

void
pnp_freeinfo(struct pnpinfo *pi)
{
    struct pnpident	*id;

    while (!STAILQ_EMPTY(&pi->pi_ident)) {
	id = STAILQ_FIRST(&pi->pi_ident);
	STAILQ_REMOVE_HEAD(&pi->pi_ident, id_link);
	free(id->id_ident);
	free(id);
    }
    if (pi->pi_desc)
	free(pi->pi_desc);
    if (pi->pi_module)
	free(pi->pi_module);
    if (pi->pi_argv)
	free(pi->pi_argv);
    free(pi);
}