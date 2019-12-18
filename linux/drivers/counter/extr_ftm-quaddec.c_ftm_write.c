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
typedef  scalar_t__ uint32_t ;
struct ftm_quaddec {scalar_t__ ftm_base; scalar_t__ big_endian; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void ftm_write(struct ftm_quaddec *ftm, uint32_t offset, uint32_t data)
{
	if (ftm->big_endian)
		iowrite32be(data, ftm->ftm_base + offset);
	else
		iowrite32(data, ftm->ftm_base + offset);
}