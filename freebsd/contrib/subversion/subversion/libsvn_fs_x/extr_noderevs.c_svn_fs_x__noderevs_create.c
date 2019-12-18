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
typedef  int /*<<< orphan*/  svn_fs_x__representation_t ;
struct TYPE_4__ {void* noderevs; void* reps; void* ids; int /*<<< orphan*/ * paths; void* reps_dict; void* ids_dict; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ svn_fs_x__noderevs_t ;
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
typedef  int /*<<< orphan*/  binary_noderev_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_fs_x__string_table_builder_create (int /*<<< orphan*/ *) ; 
 void* svn_hash__make (int /*<<< orphan*/ *) ; 

svn_fs_x__noderevs_t *
svn_fs_x__noderevs_create(int initial_count,
                          apr_pool_t* result_pool)
{
  svn_fs_x__noderevs_t *noderevs
    = apr_palloc(result_pool, sizeof(*noderevs));

  noderevs->builder = svn_fs_x__string_table_builder_create(result_pool);
  noderevs->ids_dict = svn_hash__make(result_pool);
  noderevs->reps_dict = svn_hash__make(result_pool);
  noderevs->paths = NULL;

  noderevs->ids
    = apr_array_make(result_pool, 2 * initial_count, sizeof(svn_fs_x__id_t));
  noderevs->reps
    = apr_array_make(result_pool, 2 * initial_count,
                     sizeof(svn_fs_x__representation_t));
  noderevs->noderevs
    = apr_array_make(result_pool, initial_count, sizeof(binary_noderev_t));

  return noderevs;
}