#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct set_uuid_args {int /*<<< orphan*/  uuid; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_fs_bdb__set_uuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_set_uuid(void *baton, trail_t *trail)
{
  struct set_uuid_args *args = baton;
  return svn_fs_bdb__set_uuid(trail->fs, args->idx, args->uuid,
                              trail, trail->pool);
}