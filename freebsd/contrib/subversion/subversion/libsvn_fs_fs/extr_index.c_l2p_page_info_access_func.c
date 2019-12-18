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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  l2p_page_table_entry_t ;
struct TYPE_4__ {int /*<<< orphan*/  page_table_index; int /*<<< orphan*/  page_table; } ;
typedef  TYPE_1__ l2p_header_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * l2p_page_info_copy (void*,TYPE_1__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 void* svn_temp_deserializer__ptr (TYPE_1__ const*,void const* const*) ; 

__attribute__((used)) static svn_error_t *
l2p_page_info_access_func(void **out,
                          const void *data,
                          apr_size_t data_len,
                          void *baton,
                          apr_pool_t *result_pool)
{
  /* resolve all pointer values of in-cache data */
  const l2p_header_t *header = data;
  const l2p_page_table_entry_t *page_table
    = svn_temp_deserializer__ptr(header,
                                 (const void *const *)&header->page_table);
  const apr_size_t *page_table_index
    = svn_temp_deserializer__ptr(header,
                           (const void *const *)&header->page_table_index);

  /* copy the info */
  return l2p_page_info_copy(baton, header, page_table, page_table_index,
                            result_pool);
}