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
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_5__ {scalar_t__ size; void* data; } ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/  svn_fs_base__clear_dbt (TYPE_1__*) ; 

DBT *
svn_fs_base__set_dbt(DBT *dbt, const void *data, apr_size_t size)
{
  svn_fs_base__clear_dbt(dbt);

  dbt->data = (void *) data;
  dbt->size = (u_int32_t) size;

  return dbt;
}