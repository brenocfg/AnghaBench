#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t size; TYPE_3__* sub_tables; } ;
typedef  TYPE_2__ string_table_t ;
struct TYPE_10__ {size_t long_string_count; size_t short_string_count; TYPE_4__* short_strings; TYPE_1__* long_strings; } ;
typedef  TYPE_3__ string_sub_table_t ;
struct TYPE_11__ {size_t head_length; size_t tail_length; } ;
typedef  TYPE_4__ string_header_t ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {size_t len; char* data; } ;

/* Variables and functions */
 size_t LONG_STRING_MASK ; 
 size_t PADDING ; 
 size_t STRING_INDEX_MASK ; 
 size_t TABLE_SHIFT ; 
 char* apr_palloc (int /*<<< orphan*/ *,size_t) ; 
 char const* apr_pstrmemdup (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  table_copy_string (char*,size_t,TYPE_3__*,TYPE_4__*) ; 

const char*
svn_fs_x__string_table_get(const string_table_t *table,
                           apr_size_t idx,
                           apr_size_t *length,
                           apr_pool_t *result_pool)
{
  apr_size_t table_number = idx >> TABLE_SHIFT;
  apr_size_t sub_index = idx & STRING_INDEX_MASK;

  if (table_number < table->size)
    {
      string_sub_table_t *sub_table = &table->sub_tables[table_number];
      if (idx & LONG_STRING_MASK)
        {
          if (sub_index < sub_table->long_string_count)
            {
              if (length)
                *length = sub_table->long_strings[sub_index].len;

              return apr_pstrmemdup(result_pool,
                                    sub_table->long_strings[sub_index].data,
                                    sub_table->long_strings[sub_index].len);
            }
        }
      else
        {
          if (sub_index < sub_table->short_string_count)
            {
              string_header_t *header = sub_table->short_strings + sub_index;
              apr_size_t len = header->head_length + header->tail_length;
              char *result = apr_palloc(result_pool, len + PADDING);

              if (length)
                *length = len;
              table_copy_string(result, len, sub_table, header);

              return result;
            }
        }
    }

  return apr_pstrmemdup(result_pool, "", 0);
}