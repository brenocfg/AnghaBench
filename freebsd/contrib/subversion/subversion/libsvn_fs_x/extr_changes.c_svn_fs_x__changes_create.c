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
struct TYPE_4__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ svn_fs_x__changes_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* changes_create_body (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__string_table_builder_create (int /*<<< orphan*/ *) ; 

svn_fs_x__changes_t *
svn_fs_x__changes_create(apr_size_t initial_count,
                         apr_pool_t *result_pool)
{
  svn_fs_x__changes_t *changes = changes_create_body(initial_count,
                                                     result_pool);
  changes->builder = svn_fs_x__string_table_builder_create(result_pool);

  return changes;
}