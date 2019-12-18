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
typedef  enum vf_mode { ____Placeholder_vf_mode } vf_mode ;

/* Variables and functions */
 int MAX_PF_QUEUES ; 
#define  __NDEV_MODE_PF 132 
#define  __NDEV_MODE_VF128 131 
#define  __NDEV_MODE_VF16 130 
#define  __NDEV_MODE_VF32 129 
#define  __NDEV_MODE_VF64 128 

__attribute__((used)) static inline int vf_mode_to_nr_queues(enum vf_mode mode)
{
	int nr_queues = 0;

	switch (mode) {
	case __NDEV_MODE_PF:
		nr_queues = MAX_PF_QUEUES;
		break;
	case __NDEV_MODE_VF16:
		nr_queues = 8;
		break;
	case __NDEV_MODE_VF32:
		nr_queues = 4;
		break;
	case __NDEV_MODE_VF64:
		nr_queues = 2;
		break;
	case __NDEV_MODE_VF128:
		nr_queues = 1;
		break;
	}

	return nr_queues;
}