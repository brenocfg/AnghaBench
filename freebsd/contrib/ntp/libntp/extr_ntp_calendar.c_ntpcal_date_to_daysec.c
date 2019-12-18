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
struct calendar {int /*<<< orphan*/  second; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ntpcal_etime_to_seconds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t
ntpcal_date_to_daysec(
	const struct calendar *jd
	)
{
	return ntpcal_etime_to_seconds(jd->hour, jd->minute,
				       jd->second);
}