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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  ICL_UNC_CBO_CONFIG ; 
 int ICL_UNC_NUM_CBO_MASK ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int icl_get_cbox_num(void)
{
	u64 num_boxes;

	rdmsrl(ICL_UNC_CBO_CONFIG, num_boxes);

	return num_boxes & ICL_UNC_NUM_CBO_MASK;
}