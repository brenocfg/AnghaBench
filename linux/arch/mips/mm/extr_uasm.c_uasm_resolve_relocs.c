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
struct uasm_reloc {scalar_t__ lab; } ;
struct uasm_label {scalar_t__ lab; } ;

/* Variables and functions */
 scalar_t__ UASM_LABEL_INVALID ; 
 int /*<<< orphan*/  __resolve_relocs (struct uasm_reloc*,struct uasm_label*) ; 

void uasm_resolve_relocs(struct uasm_reloc *rel,
				  struct uasm_label *lab)
{
	struct uasm_label *l;

	for (; rel->lab != UASM_LABEL_INVALID; rel++)
		for (l = lab; l->lab != UASM_LABEL_INVALID; l++)
			if (rel->lab == l->lab)
				__resolve_relocs(rel, l);
}