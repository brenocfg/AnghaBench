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
struct TYPE_4__ {int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ svn_checksum_t ;
typedef  int /*<<< orphan*/  DBT ;

/* Variables and functions */
 int /*<<< orphan*/  svn_checksum_size (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_fs_base__set_dbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DBT *
svn_fs_base__checksum_to_dbt(DBT *dbt, svn_checksum_t *checksum)
{
  svn_fs_base__set_dbt(dbt, checksum->digest, svn_checksum_size(checksum));

  return dbt;
}