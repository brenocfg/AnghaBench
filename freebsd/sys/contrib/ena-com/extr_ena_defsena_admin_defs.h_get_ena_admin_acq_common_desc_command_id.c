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
typedef  int uint16_t ;
struct ena_admin_acq_common_desc {int command; } ;

/* Variables and functions */
 int ENA_ADMIN_ACQ_COMMON_DESC_COMMAND_ID_MASK ; 

__attribute__((used)) static inline uint16_t get_ena_admin_acq_common_desc_command_id(const struct ena_admin_acq_common_desc *p)
{
	return p->command & ENA_ADMIN_ACQ_COMMON_DESC_COMMAND_ID_MASK;
}