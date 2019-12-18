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
struct qm_mr {struct qm_mr_entry* cursor; int /*<<< orphan*/  fill; } ;
struct qm_portal {struct qm_mr mr; } ;
struct qm_mr_entry {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static __inline__ struct qm_mr_entry *qm_mr_current(struct qm_portal *portal)
{
    register struct qm_mr *mr = &portal->mr;
    if (!mr->fill)
        return NULL;
    return mr->cursor;
}