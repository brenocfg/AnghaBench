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
typedef  int /*<<< orphan*/  uint64_t ;
struct os_area_db {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int db_get_64 (struct os_area_db const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_area_db_id_rtc_diff ; 

__attribute__((used)) static int db_get_rtc_diff(const struct os_area_db *db, int64_t *rtc_diff)
{
	return db_get_64(db, &os_area_db_id_rtc_diff, (uint64_t*)rtc_diff);
}