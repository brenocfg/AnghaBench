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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/ * sa_idx_tab; int /*<<< orphan*/ * sa_variable_lengths; } ;
typedef  TYPE_1__ sa_idx_tab_t ;
typedef  size_t sa_attr_type_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TOC_ATTR_ENCODE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
sa_build_idx_tab(void *hdr, void *attr_addr, sa_attr_type_t attr,
    uint16_t length, int length_idx, boolean_t var_length, void *userp)
{
	sa_idx_tab_t *idx_tab = userp;

	if (var_length) {
		ASSERT(idx_tab->sa_variable_lengths);
		idx_tab->sa_variable_lengths[length_idx] = length;
	}
	TOC_ATTR_ENCODE(idx_tab->sa_idx_tab[attr], length_idx,
	    (uint32_t)((uintptr_t)attr_addr - (uintptr_t)hdr));
}