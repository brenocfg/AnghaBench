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
struct qm_addr {int /*<<< orphan*/  addr_ce; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_ADD (int /*<<< orphan*/ ,uintptr_t) ; 

__attribute__((used)) static __inline__ void __qm_cl_invalidate(struct qm_addr *qm, uintptr_t offset)
{
    dcbi(ptr_ADD(qm->addr_ce, offset));
}