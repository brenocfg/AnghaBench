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
typedef  int /*<<< orphan*/  uint16_t ;
struct sa_query_result {int dummy; } ;
struct sa_handle {int dummy; } ;

/* Variables and functions */
 int get_any_records (struct sa_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sa_query_result*) ; 

__attribute__((used)) static int get_all_records(struct sa_handle * h, uint16_t attr_id,
			   struct sa_query_result *result)
{
	return get_any_records(h, attr_id, 0, 0, NULL, 0, result);
}