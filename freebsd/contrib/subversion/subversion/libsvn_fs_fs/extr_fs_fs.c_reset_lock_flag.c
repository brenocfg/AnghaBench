#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  has_write_lock; } ;
typedef  TYPE_1__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static apr_status_t
reset_lock_flag(void *baton_void)
{
  fs_fs_data_t *ffd = baton_void;
  ffd->has_write_lock = FALSE;
  return APR_SUCCESS;
}