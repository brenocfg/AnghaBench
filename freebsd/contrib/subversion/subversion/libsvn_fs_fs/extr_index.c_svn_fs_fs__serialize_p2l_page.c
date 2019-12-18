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
typedef  int /*<<< orphan*/  svn_temp_serializer__context_t ;
struct TYPE_5__ {int len; void* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int elt_size; int nelts; int /*<<< orphan*/  elts; } ;
typedef  TYPE_2__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_temp_serializer__add_leaf (int /*<<< orphan*/ *,void const* const*,int) ; 
 TYPE_1__* svn_temp_serializer__get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_temp_serializer__init (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__serialize_p2l_page(void **data,
                              apr_size_t *data_len,
                              void *in,
                              apr_pool_t *pool)
{
  apr_array_header_t *page = in;
  svn_temp_serializer__context_t *context;
  svn_stringbuf_t *serialized;
  apr_size_t table_size = page->elt_size * page->nelts;

  /* serialize array header and all its elements */
  context = svn_temp_serializer__init(page,
                                      sizeof(*page),
                                      table_size + sizeof(*page) + 32,
                                      pool);

  /* items in the array */
  svn_temp_serializer__add_leaf(context,
                                (const void * const *)&page->elts,
                                table_size);

  /* return the serialized result */
  serialized = svn_temp_serializer__get(context);

  *data = serialized->data;
  *data_len = serialized->len;

  return SVN_NO_ERROR;
}