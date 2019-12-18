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
typedef  int u8 ;
typedef  int u32 ;
struct reset_controller_dev {int dummy; } ;
struct of_phandle_args {int* args; } ;

/* Variables and functions */
 int HISI_RESET_BIT_MASK ; 
 int HISI_RESET_OFFSET_MASK ; 
 int HISI_RESET_OFFSET_SHIFT ; 

__attribute__((used)) static int hisi_reset_of_xlate(struct reset_controller_dev *rcdev,
			const struct of_phandle_args *reset_spec)
{
	u32 offset;
	u8 bit;

	offset = (reset_spec->args[0] << HISI_RESET_OFFSET_SHIFT)
		& HISI_RESET_OFFSET_MASK;
	bit = reset_spec->args[1] & HISI_RESET_BIT_MASK;

	return (offset | bit);
}