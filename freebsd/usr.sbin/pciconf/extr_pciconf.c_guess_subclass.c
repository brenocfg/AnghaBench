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
struct pci_conf {scalar_t__ pc_class; scalar_t__ pc_subclass; } ;
struct TYPE_2__ {char const* desc; scalar_t__ class; scalar_t__ subclass; } ;

/* Variables and functions */
 TYPE_1__* pci_nomatch_tab ; 

__attribute__((used)) static const char *
guess_subclass(struct pci_conf *p)
{
	int	i;

	for (i = 0; pci_nomatch_tab[i].desc != NULL; i++) {
		if ((pci_nomatch_tab[i].class == p->pc_class) &&
		    (pci_nomatch_tab[i].subclass == p->pc_subclass))
			return(pci_nomatch_tab[i].desc);
	}
	return(NULL);
}