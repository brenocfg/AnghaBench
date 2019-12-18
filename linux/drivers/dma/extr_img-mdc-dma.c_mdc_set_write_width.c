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
struct mdc_hw_list_desc {int gen_conf; } ;

/* Variables and functions */
 int MDC_GENERAL_CONFIG_WIDTH_W_SHIFT ; 
 int to_mdc_width (unsigned int) ; 

__attribute__((used)) static inline void mdc_set_write_width(struct mdc_hw_list_desc *ldesc,
				       unsigned int bytes)
{
	ldesc->gen_conf |= to_mdc_width(bytes) <<
		MDC_GENERAL_CONFIG_WIDTH_W_SHIFT;
}