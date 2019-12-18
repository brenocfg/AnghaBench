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
struct TYPE_5__ {int /*<<< orphan*/  tables; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ string_table_builder_t ;
typedef  int /*<<< orphan*/  builder_table_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_table (TYPE_1__*) ; 
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 

string_table_builder_t *
svn_fs_x__string_table_builder_create(apr_pool_t *result_pool)
{
  string_table_builder_t *result = apr_palloc(result_pool, sizeof(*result));
  result->pool = result_pool;
  result->tables = apr_array_make(result_pool, 1, sizeof(builder_table_t *));

  add_table(result);

  return result;
}