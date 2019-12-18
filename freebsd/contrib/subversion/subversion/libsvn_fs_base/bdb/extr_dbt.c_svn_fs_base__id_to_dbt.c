#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  DBT ;

/* Variables and functions */
 TYPE_1__* svn_fs_base__id_unparse (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__set_dbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DBT *
svn_fs_base__id_to_dbt(DBT *dbt,
                       const svn_fs_id_t *id,
                       apr_pool_t *pool)
{
  svn_string_t *unparsed_id = svn_fs_base__id_unparse(id, pool);
  svn_fs_base__set_dbt(dbt, unparsed_id->data, unparsed_id->len);
  return dbt;
}