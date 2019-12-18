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
struct TYPE_7__ {TYPE_5__* offsets; TYPE_5__* changes; int /*<<< orphan*/  paths; } ;
typedef  TYPE_2__ svn_fs_x__changes_t ;
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
svn_fs_x__serialize_changes_container(void **data,
                                      apr_size_t *data_len,
                                      void *in,
                                      apr_pool_t *pool)
{
  svn_fs_x__changes_t *changes = in;
  svn_stringbuf_t *serialized;

  /* make a guesstimate on the size of the serialized data.  Erring on the
   * low side will cause the serializer to re-alloc its buffer. */
  apr_size_t size
    = changes->changes->elt_size * changes->changes->nelts
    + changes->offsets->elt_size * changes->offsets->nelts
    + 10 * changes->changes->elt_size
    + 100;

  /* serialize array header and all its elements */
  svn_temp_serializer__context_t *context
    = svn_temp_serializer__init(changes, sizeof(*changes), size, pool);

  /* serialize sub-structures */
  svn_fs_x__serialize_string_table(context, &changes->paths);
  svn_fs_x__serialize_apr_array(context, &changes->changes);
  svn_fs_x__serialize_apr_array(context, &changes->offsets);

  /* return the serialized result */
  serialized = svn_temp_serializer__get(context);

  *data = serialized->data;
  *data_len = serialized->len;

  return SVN_NO_ERROR;
}