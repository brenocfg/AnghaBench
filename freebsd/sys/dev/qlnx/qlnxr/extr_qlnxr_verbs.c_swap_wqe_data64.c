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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int QLNXR_SQE_ELEMENT_SIZE ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
swap_wqe_data64(u64 *p)
{
	int i;

	for (i = 0; i < QLNXR_SQE_ELEMENT_SIZE / sizeof(u64); i++, p++)
		*p = cpu_to_be64(cpu_to_le64(*p));
}