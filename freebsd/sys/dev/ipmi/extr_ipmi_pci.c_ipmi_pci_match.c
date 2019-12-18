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
typedef  scalar_t__ uint16_t ;
struct ipmi_ident {scalar_t__ vendor; scalar_t__ device; char const* desc; } ;

/* Variables and functions */
 struct ipmi_ident* ipmi_identifiers ; 

const char *
ipmi_pci_match(uint16_t vendor, uint16_t device)
{
	struct ipmi_ident *m;

	for (m = ipmi_identifiers; m->vendor != 0; m++)
		if (m->vendor == vendor && m->device == device)
			return (m->desc);
	return (NULL);
}