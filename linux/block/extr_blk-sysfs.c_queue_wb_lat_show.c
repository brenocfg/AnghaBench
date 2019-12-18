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
struct request_queue {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  div_u64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbt_get_min_lat (struct request_queue*) ; 
 int /*<<< orphan*/  wbt_rq_qos (struct request_queue*) ; 

__attribute__((used)) static ssize_t queue_wb_lat_show(struct request_queue *q, char *page)
{
	if (!wbt_rq_qos(q))
		return -EINVAL;

	return sprintf(page, "%llu\n", div_u64(wbt_get_min_lat(q), 1000));
}