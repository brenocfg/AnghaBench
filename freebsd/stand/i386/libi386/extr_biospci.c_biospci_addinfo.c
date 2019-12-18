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
struct pnpinfo {int /*<<< orphan*/  pi_desc; } ;
struct pci_subclass {char* ps_name; } ;
struct pci_progif {char* pi_name; } ;
struct pci_class {char* pc_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pnp_addident (struct pnpinfo*,char*) ; 
 int /*<<< orphan*/  pnp_addinfo (struct pnpinfo*) ; 
 struct pnpinfo* pnp_allocinfo () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static void
biospci_addinfo(int devid, struct pci_class *pc, struct pci_subclass *psc, struct pci_progif *ppi) 
{
    struct pnpinfo	*pi;
    char		desc[80];
    
    
    /* build the description */
    desc[0] = 0;
    if (ppi->pi_name != NULL) {
	strcat(desc, ppi->pi_name);
	strcat(desc, " ");
    }
    if (psc->ps_name != NULL) {
	strcat(desc, psc->ps_name);
	strcat(desc, " ");
    }
    if (pc->pc_name != NULL)
	strcat(desc, pc->pc_name);

    pi = pnp_allocinfo();
    pi->pi_desc = strdup(desc);
    sprintf(desc,"0x%08x", devid);
    pnp_addident(pi, desc);
    pnp_addinfo(pi);
}