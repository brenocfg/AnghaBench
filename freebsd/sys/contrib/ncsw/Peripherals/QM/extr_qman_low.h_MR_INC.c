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
struct qm_mr_entry {int dummy; } ;

/* Variables and functions */
 struct qm_mr_entry* MR_CARRYCLEAR (struct qm_mr_entry*) ; 

__attribute__((used)) static __inline__ struct qm_mr_entry *MR_INC(struct qm_mr_entry *e)
{
    return MR_CARRYCLEAR(e + 1);
}