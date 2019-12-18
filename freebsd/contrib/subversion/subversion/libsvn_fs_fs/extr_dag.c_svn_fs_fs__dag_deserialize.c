#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  created_path; int /*<<< orphan*/ * node_pool; int /*<<< orphan*/  node_revision; int /*<<< orphan*/  fresh_root_predecessor_id; int /*<<< orphan*/ * id; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ dag_node_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__id_deserialize (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  svn_fs_fs__noderev_deserialize (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_temp_deserializer__resolve (TYPE_1__*,void**) ; 

svn_error_t *
svn_fs_fs__dag_deserialize(void **out,
                           void *data,
                           apr_size_t data_len,
                           apr_pool_t *pool)
{
  dag_node_t *node = (dag_node_t *)data;
  if (data_len == 0)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Empty noderev in cache"));

  /* Copy the _full_ buffer as it also contains the sub-structures. */
  node->fs = NULL;

  /* fixup all references to sub-structures */
  svn_fs_fs__id_deserialize(node, &node->id);
  svn_fs_fs__id_deserialize(node,
                            (svn_fs_id_t **)&node->fresh_root_predecessor_id);
  svn_fs_fs__noderev_deserialize(node, &node->node_revision);
  node->node_pool = pool;

  svn_temp_deserializer__resolve(node, (void**)&node->created_path);

  /* return result */
  *out = node;

  return SVN_NO_ERROR;
}