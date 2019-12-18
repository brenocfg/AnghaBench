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
struct TYPE_4__ {int nelts; int nalloc; int /*<<< orphan*/ * pool; int /*<<< orphan*/  items; scalar_t__ elts; } ;
typedef  TYPE_1__ svn_fs_x__p2l_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  TYPE_1__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_temp_deserializer__resolve (TYPE_1__*,void**) ; 

svn_error_t *
svn_fs_x__deserialize_p2l_page(void **out,
                               void *data,
                               apr_size_t data_len,
                               apr_pool_t *result_pool)
{
  apr_array_header_t *page = (apr_array_header_t *)data;
  svn_fs_x__p2l_entry_t *entries;
  int i;

  /* resolve the only pointer in the struct */
  svn_temp_deserializer__resolve(page, (void**)&page->elts);

  /* resolve sub-struct pointers*/
  entries = (svn_fs_x__p2l_entry_t *)page->elts;
  for (i = 0; i < page->nelts; ++i)
    svn_temp_deserializer__resolve(entries, (void**)&entries[i].items);

  /* patch up members */
  page->pool = result_pool;
  page->nalloc = page->nelts;

  /* done */
  *out = page;

  return SVN_NO_ERROR;
}