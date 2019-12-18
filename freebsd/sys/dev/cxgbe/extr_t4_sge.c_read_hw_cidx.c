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
struct sge_qstat {int /*<<< orphan*/  cidx; } ;
struct sge_eq {size_t sidx; int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint16_t
read_hw_cidx(struct sge_eq *eq)
{
	struct sge_qstat *spg = (void *)&eq->desc[eq->sidx];
	uint16_t cidx = spg->cidx;	/* stable snapshot */

	return (be16toh(cidx));
}