#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ghes {TYPE_2__* generic; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */
 scalar_t__ ACPI_HEST_TYPE_GENERIC_ERROR_V2 ; 

__attribute__((used)) static inline bool is_hest_type_generic_v2(struct ghes *ghes)
{
	return ghes->generic->header.type == ACPI_HEST_TYPE_GENERIC_ERROR_V2;
}