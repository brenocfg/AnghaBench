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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_NOMERGES ; 
 int /*<<< orphan*/  QUEUE_FLAG_NOXMERGES ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 scalar_t__ queue_var_store (unsigned long*,char const*,size_t) ; 

__attribute__((used)) static ssize_t queue_nomerges_store(struct request_queue *q, const char *page,
				    size_t count)
{
	unsigned long nm;
	ssize_t ret = queue_var_store(&nm, page, count);

	if (ret < 0)
		return ret;

	blk_queue_flag_clear(QUEUE_FLAG_NOMERGES, q);
	blk_queue_flag_clear(QUEUE_FLAG_NOXMERGES, q);
	if (nm == 2)
		blk_queue_flag_set(QUEUE_FLAG_NOMERGES, q);
	else if (nm)
		blk_queue_flag_set(QUEUE_FLAG_NOXMERGES, q);

	return ret;
}