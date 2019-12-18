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
typedef  TYPE_1__* uma_zone_t ;
struct timeval {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_3__ {char* uz_warning; char* uz_name; int /*<<< orphan*/  uz_ratecheck; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 scalar_t__ ratecheck (int /*<<< orphan*/ *,struct timeval const*) ; 
 int /*<<< orphan*/  zone_warnings ; 

__attribute__((used)) static void
zone_log_warning(uma_zone_t zone)
{
	static const struct timeval warninterval = { 300, 0 };

	if (!zone_warnings || zone->uz_warning == NULL)
		return;

	if (ratecheck(&zone->uz_ratecheck, &warninterval))
		printf("[zone: %s] %s\n", zone->uz_name, zone->uz_warning);
}