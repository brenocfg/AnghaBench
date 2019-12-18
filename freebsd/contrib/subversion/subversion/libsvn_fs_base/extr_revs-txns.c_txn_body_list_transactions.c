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
struct TYPE_4__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct list_transactions_args {int /*<<< orphan*/  pool; int /*<<< orphan*/  names_p; } ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_fs_bdb__get_txn_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_list_transactions(void* baton, trail_t *trail)
{
  struct list_transactions_args *args = baton;
  return svn_fs_bdb__get_txn_list(args->names_p, trail->fs,
                                  trail, args->pool);
}