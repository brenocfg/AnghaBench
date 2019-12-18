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
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  DBT ;

/* Variables and functions */
 int /*<<< orphan*/  svn_fs_base__set_dbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_skel__unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DBT *
svn_fs_base__skel_to_dbt(DBT *dbt,
                         svn_skel_t *skel,
                         apr_pool_t *pool)
{
  svn_stringbuf_t *unparsed_skel = svn_skel__unparse(skel, pool);
  svn_fs_base__set_dbt(dbt, unparsed_skel->data, unparsed_skel->len);
  return dbt;
}