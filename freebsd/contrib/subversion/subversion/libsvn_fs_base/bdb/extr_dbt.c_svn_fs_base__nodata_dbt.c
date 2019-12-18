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
struct TYPE_5__ {int flags; scalar_t__ dlen; scalar_t__ doff; } ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 int DB_DBT_PARTIAL ; 
 int DB_DBT_USERMEM ; 
 int /*<<< orphan*/  svn_fs_base__clear_dbt (TYPE_1__*) ; 

DBT *svn_fs_base__nodata_dbt(DBT *dbt)
{
  svn_fs_base__clear_dbt(dbt);

  /* A `nodata' dbt is one which retrieves zero bytes from offset zero,
     and stores them in a zero-byte buffer in user-allocated memory.  */
  dbt->flags |= (DB_DBT_USERMEM | DB_DBT_PARTIAL);
  dbt->doff = dbt->dlen = 0;

  return dbt;
}