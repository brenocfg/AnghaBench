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
struct request {int dummy; } ;
struct driver_data {int dd_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTIP_DDF_OVER_TEMP_BIT ; 
 int /*<<< orphan*/  MTIP_DDF_REBUILD_FAILED_BIT ; 
 int /*<<< orphan*/  MTIP_DDF_REMOVE_PENDING_BIT ; 
 int /*<<< orphan*/  MTIP_DDF_SEC_LOCK_BIT ; 
 int MTIP_DDF_STOP_IO ; 
 int /*<<< orphan*/  MTIP_DDF_WRITE_PROTECT_BIT ; 
 scalar_t__ likely (int) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline bool is_stopped(struct driver_data *dd, struct request *rq)
{
	if (likely(!(dd->dd_flag & MTIP_DDF_STOP_IO)))
		return false;

	if (test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &dd->dd_flag))
		return true;
	if (test_bit(MTIP_DDF_OVER_TEMP_BIT, &dd->dd_flag))
		return true;
	if (test_bit(MTIP_DDF_WRITE_PROTECT_BIT, &dd->dd_flag) &&
	    rq_data_dir(rq))
		return true;
	if (test_bit(MTIP_DDF_SEC_LOCK_BIT, &dd->dd_flag))
		return true;
	if (test_bit(MTIP_DDF_REBUILD_FAILED_BIT, &dd->dd_flag))
		return true;

	return false;
}