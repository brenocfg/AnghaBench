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
typedef  int /*<<< orphan*/  uint64_t ;
struct nicvf {int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_read_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t
nicvf_reg_read(struct nicvf *nic, uint64_t offset)
{

	return (bus_read_8(nic->reg_base, offset));
}