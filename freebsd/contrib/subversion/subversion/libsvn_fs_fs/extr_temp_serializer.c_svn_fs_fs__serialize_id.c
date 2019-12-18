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
typedef  int /*<<< orphan*/  svn_temp_serializer__context_t ;
struct TYPE_3__ {int /*<<< orphan*/  len; void* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__id_serialize (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 TYPE_1__* svn_temp_serializer__get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_temp_serializer__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__serialize_id(void **data,
                        apr_size_t *data_len,
                        void *in,
                        apr_pool_t *pool)
{
  const svn_fs_id_t *id = in;
  svn_stringbuf_t *serialized;

  /* create an (empty) serialization context with plenty of buffer space */
  svn_temp_serializer__context_t *context =
      svn_temp_serializer__init(NULL, 0, 250, pool);

  /* serialize the id */
  svn_fs_fs__id_serialize(context, &id);

  /* return serialized data */
  serialized = svn_temp_serializer__get(context);
  *data = serialized->data;
  *data_len = serialized->len;

  return SVN_NO_ERROR;
}