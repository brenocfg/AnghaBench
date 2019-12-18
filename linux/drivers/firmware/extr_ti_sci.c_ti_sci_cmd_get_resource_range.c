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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ti_sci_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TI_SCI_IRQ_SECONDARY_HOST_INVALID ; 
 int ti_sci_get_resource_range (struct ti_sci_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ti_sci_cmd_get_resource_range(const struct ti_sci_handle *handle,
					 u32 dev_id, u8 subtype,
					 u16 *range_start, u16 *range_num)
{
	return ti_sci_get_resource_range(handle, dev_id, subtype,
					 TI_SCI_IRQ_SECONDARY_HOST_INVALID,
					 range_start, range_num);
}