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
struct mthca_eqe {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTHCA_EQ_ENTRY_OWNER_HW ; 

__attribute__((used)) static inline void set_eqe_hw(struct mthca_eqe *eqe)
{
	eqe->owner =  MTHCA_EQ_ENTRY_OWNER_HW;
}