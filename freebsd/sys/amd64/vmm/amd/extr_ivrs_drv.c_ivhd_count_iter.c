#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Type; } ;
typedef  TYPE_1__ ACPI_IVRS_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ivhd_count ; 
 scalar_t__ ivrs_is_ivhd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ivhd_count_iter(ACPI_IVRS_HEADER * ivrs_he, void *arg)
{

	if (ivrs_is_ivhd(ivrs_he->Type))
		ivhd_count++;

	return (1);
}