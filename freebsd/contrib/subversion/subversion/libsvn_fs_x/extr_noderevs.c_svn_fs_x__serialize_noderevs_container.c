#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_temp_serializer__context_t ;
struct TYPE_6__ {int len; void* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_7__ {TYPE_5__* noderevs; TYPE_5__* reps; TYPE_5__* ids; int /*<<< orphan*/  paths; } ;
typedef  TYPE_2__ svn_fs_x__noderevs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {int elt_size; int nelts; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_x__serialize_apr_array (int /*<<< orphan*/ *,TYPE_5__**) ; 
 int /*<<< orphan*/  svn_fs_x__serialize_string_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_temp_serializer__get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_temp_serializer__init (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__serialize_noderevs_container(void **data,
                                       apr_size_t *data_len,
                                       void *in,
                                       apr_pool_t *pool)
{
  svn_fs_x__noderevs_t *noderevs = in;
  svn_stringbuf_t *serialized;
  apr_size_t size
    = noderevs->ids->elt_size * noderevs->ids->nelts
    + noderevs->reps->elt_size * noderevs->reps->nelts
    + noderevs->noderevs->elt_size * noderevs->noderevs->nelts
    + 10 * noderevs->noderevs->elt_size
    + 100;

  /* serialize array header and all its elements */
  svn_temp_serializer__context_t *context
    = svn_temp_serializer__init(noderevs, sizeof(*noderevs), size, pool);

  /* serialize sub-structures */
  svn_fs_x__serialize_string_table(context, &noderevs->paths);
  svn_fs_x__serialize_apr_array(context, &noderevs->ids);
  svn_fs_x__serialize_apr_array(context, &noderevs->reps);
  svn_fs_x__serialize_apr_array(context, &noderevs->noderevs);

  /* return the serialized result */
  serialized = svn_temp_serializer__get(context);

  *data = serialized->data;
  *data_len = serialized->len;

  return SVN_NO_ERROR;
}