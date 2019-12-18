#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_temp_serializer__context_t ;
struct TYPE_6__ {int /*<<< orphan*/  len; void* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/  created_path; int /*<<< orphan*/  const* fresh_root_predecessor_id; int /*<<< orphan*/  id; int /*<<< orphan*/  node_pool; scalar_t__ node_revision; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_TEMP_SERIALIZER__OVERHEAD ; 
 int /*<<< orphan*/  svn_fs_fs__dag_check_mutable (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_fs__id_serialize (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  svn_fs_fs__noderev_serialize (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  svn_temp_serializer__add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_temp_serializer__get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_temp_serializer__init (TYPE_2__*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_temp_serializer__set_null (int /*<<< orphan*/ *,void const* const*) ; 

svn_error_t *
svn_fs_fs__dag_serialize(void **data,
                         apr_size_t *data_len,
                         void *in,
                         apr_pool_t *pool)
{
  dag_node_t *node = in;
  svn_stringbuf_t *serialized;

  /* create an serialization context and serialize the dag node as root */
  svn_temp_serializer__context_t *context =
      svn_temp_serializer__init(node,
                                sizeof(*node),
                                1024 - SVN_TEMP_SERIALIZER__OVERHEAD,
                                pool);

  /* for mutable nodes, we will _never_ cache the noderev */
  if (node->node_revision && !svn_fs_fs__dag_check_mutable(node))
    svn_fs_fs__noderev_serialize(context, &node->node_revision);
  else
    svn_temp_serializer__set_null(context,
                                  (const void * const *)&node->node_revision);

  /* The deserializer will use its own pool. */
  svn_temp_serializer__set_null(context,
                                (const void * const *)&node->node_pool);

  /* serialize other sub-structures */
  svn_fs_fs__id_serialize(context, (const svn_fs_id_t **)&node->id);
  svn_fs_fs__id_serialize(context, &node->fresh_root_predecessor_id);
  svn_temp_serializer__add_string(context, &node->created_path);

  /* return serialized data */
  serialized = svn_temp_serializer__get(context);
  *data = serialized->data;
  *data_len = serialized->len;

  return SVN_NO_ERROR;
}