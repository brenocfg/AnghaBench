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
struct TYPE_2__ {int mode; } ;
struct tree_desc {TYPE_1__ entry; } ;

/* Variables and functions */
 int S_IFXMIN_NEQ ; 
 int /*<<< orphan*/  update_tree_entry (struct tree_desc*) ; 

__attribute__((used)) static inline void update_tp_entries(struct tree_desc *tp, int nparent)
{
	int i;
	for (i = 0; i < nparent; ++i)
		if (!(tp[i].entry.mode & S_IFXMIN_NEQ))
			update_tree_entry(&tp[i]);
}