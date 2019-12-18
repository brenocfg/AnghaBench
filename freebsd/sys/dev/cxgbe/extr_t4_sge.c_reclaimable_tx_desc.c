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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_int ;
struct sge_eq {int /*<<< orphan*/  sidx; int /*<<< orphan*/  cidx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDXDIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_hw_cidx (struct sge_eq*) ; 

__attribute__((used)) static inline u_int
reclaimable_tx_desc(struct sge_eq *eq)
{
	uint16_t hw_cidx;

	hw_cidx = read_hw_cidx(eq);
	return (IDXDIFF(hw_cidx, eq->cidx, eq->sidx));
}