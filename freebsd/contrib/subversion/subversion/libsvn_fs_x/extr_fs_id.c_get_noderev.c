#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_fs_x__id_context_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/ * fsap_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  noderev_id; TYPE_1__ generic_id; } ;
typedef  TYPE_2__ fs_x__id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * get_aux_pool (TYPE_2__ const*) ; 
 int /*<<< orphan*/ * get_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_x__get_node_revision (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_fs_x__noderev_t *
get_noderev(const fs_x__id_t *id)
{
  svn_fs_x__noderev_t *result = NULL;

  svn_fs_x__id_context_t *context = id->generic_id.fsap_data;
  svn_fs_t *fs = get_fs(context);
  apr_pool_t *pool = get_aux_pool(id);

  if (fs)
    {
      svn_error_t *err = svn_fs_x__get_node_revision(&result, fs,
                                                     &id->noderev_id,
                                                     pool, pool);
      if (err)
        {
          svn_error_clear(err);
          result = NULL;
        }
    }

  return result;
}