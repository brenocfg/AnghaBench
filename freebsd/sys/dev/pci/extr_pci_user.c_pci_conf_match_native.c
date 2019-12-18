#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pc_domain; scalar_t__ pc_bus; scalar_t__ pc_dev; scalar_t__ pc_func; } ;
struct pci_match_conf {int flags; scalar_t__ pc_vendor; scalar_t__ pc_device; scalar_t__ pc_class; scalar_t__ pd_unit; int /*<<< orphan*/  pd_name; TYPE_2__ pc_sel; } ;
struct TYPE_3__ {scalar_t__ pc_domain; scalar_t__ pc_bus; scalar_t__ pc_dev; scalar_t__ pc_func; } ;
struct pci_conf {scalar_t__ pc_vendor; scalar_t__ pc_device; scalar_t__ pc_class; scalar_t__ pd_unit; int /*<<< orphan*/  pd_name; TYPE_1__ pc_sel; } ;

/* Variables and functions */
 int PCI_GETCONF_MATCH_BUS ; 
 int PCI_GETCONF_MATCH_CLASS ; 
 int PCI_GETCONF_MATCH_DEV ; 
 int PCI_GETCONF_MATCH_DEVICE ; 
 int PCI_GETCONF_MATCH_DOMAIN ; 
 int PCI_GETCONF_MATCH_FUNC ; 
 int PCI_GETCONF_MATCH_NAME ; 
 int PCI_GETCONF_MATCH_UNIT ; 
 int PCI_GETCONF_MATCH_VENDOR ; 
 int PCI_GETCONF_NO_MATCH ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pci_conf_match_native(struct pci_match_conf *matches, int num_matches,
	       struct pci_conf *match_buf)
{
	int i;

	if ((matches == NULL) || (match_buf == NULL) || (num_matches <= 0))
		return(1);

	for (i = 0; i < num_matches; i++) {
		/*
		 * I'm not sure why someone would do this...but...
		 */
		if (matches[i].flags == PCI_GETCONF_NO_MATCH)
			continue;

		/*
		 * Look at each of the match flags.  If it's set, do the
		 * comparison.  If the comparison fails, we don't have a
		 * match, go on to the next item if there is one.
		 */
		if (((matches[i].flags & PCI_GETCONF_MATCH_DOMAIN) != 0)
		 && (match_buf->pc_sel.pc_domain !=
		 matches[i].pc_sel.pc_domain))
			continue;

		if (((matches[i].flags & PCI_GETCONF_MATCH_BUS) != 0)
		 && (match_buf->pc_sel.pc_bus != matches[i].pc_sel.pc_bus))
			continue;

		if (((matches[i].flags & PCI_GETCONF_MATCH_DEV) != 0)
		 && (match_buf->pc_sel.pc_dev != matches[i].pc_sel.pc_dev))
			continue;

		if (((matches[i].flags & PCI_GETCONF_MATCH_FUNC) != 0)
		 && (match_buf->pc_sel.pc_func != matches[i].pc_sel.pc_func))
			continue;

		if (((matches[i].flags & PCI_GETCONF_MATCH_VENDOR) != 0) 
		 && (match_buf->pc_vendor != matches[i].pc_vendor))
			continue;

		if (((matches[i].flags & PCI_GETCONF_MATCH_DEVICE) != 0)
		 && (match_buf->pc_device != matches[i].pc_device))
			continue;

		if (((matches[i].flags & PCI_GETCONF_MATCH_CLASS) != 0)
		 && (match_buf->pc_class != matches[i].pc_class))
			continue;

		if (((matches[i].flags & PCI_GETCONF_MATCH_UNIT) != 0)
		 && (match_buf->pd_unit != matches[i].pd_unit))
			continue;

		if (((matches[i].flags & PCI_GETCONF_MATCH_NAME) != 0)
		 && (strncmp(matches[i].pd_name, match_buf->pd_name,
			     sizeof(match_buf->pd_name)) != 0))
			continue;

		return(0);
	}

	return(1);
}