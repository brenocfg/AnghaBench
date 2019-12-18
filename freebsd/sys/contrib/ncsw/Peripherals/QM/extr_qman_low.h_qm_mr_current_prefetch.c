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
struct qm_mr {int /*<<< orphan*/  cursor; } ;
struct qm_portal {struct qm_mr mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcbt_ro (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void qm_mr_current_prefetch(struct qm_portal *portal)
{
    register struct qm_mr *mr = &portal->mr;
    dcbt_ro(mr->cursor);
}