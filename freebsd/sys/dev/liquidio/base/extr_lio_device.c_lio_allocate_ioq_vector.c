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
struct TYPE_2__ {int num_pf_rings; int pf_srn; } ;
struct octeon_device {scalar_t__ chip_id; TYPE_1__ sriov_info; struct lio_ioq_vector* ioq_vector; } ;
struct lio_ioq_vector {int droq_index; int ioq_num; int /*<<< orphan*/  affinity_mask; struct octeon_device* oct_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SETOF (int,int /*<<< orphan*/ *) ; 
 scalar_t__ LIO_CN23XX_PF (struct octeon_device*) ; 
 scalar_t__ LIO_CN23XX_PF_VID ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct lio_ioq_vector* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mp_ncpus ; 

int
lio_allocate_ioq_vector(struct octeon_device *oct)
{
	struct lio_ioq_vector	*ioq_vector;
	int	i, cpu_num, num_ioqs = 0, size;

	if (LIO_CN23XX_PF(oct))
		num_ioqs = oct->sriov_info.num_pf_rings;

	size = sizeof(struct lio_ioq_vector) * num_ioqs;

	oct->ioq_vector = malloc(size, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (oct->ioq_vector == NULL)
		return (1);

	for (i = 0; i < num_ioqs; i++) {
		ioq_vector = &oct->ioq_vector[i];
		ioq_vector->oct_dev = oct;
		ioq_vector->droq_index = i;
		cpu_num = i % mp_ncpus;
		CPU_SETOF(cpu_num, &ioq_vector->affinity_mask);

		if (oct->chip_id == LIO_CN23XX_PF_VID)
			ioq_vector->ioq_num = i + oct->sriov_info.pf_srn;
		else
			ioq_vector->ioq_num = i;
	}
	return (0);
}