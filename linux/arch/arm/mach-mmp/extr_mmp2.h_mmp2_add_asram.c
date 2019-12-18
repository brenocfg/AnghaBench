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
struct sram_platdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmp2_device_asram ; 
 int pxa_register_device (int /*<<< orphan*/ *,struct sram_platdata*,int) ; 

__attribute__((used)) static inline int mmp2_add_asram(struct sram_platdata *data)
{
	return pxa_register_device(&mmp2_device_asram, data, sizeof(*data));
}