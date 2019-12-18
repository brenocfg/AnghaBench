#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  DBT ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  svn_fs_base__set_dbt (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

DBT *
svn_fs_base__str_to_dbt(DBT *dbt, const char *str)
{
  svn_fs_base__set_dbt(dbt, str, strlen(str));
  return dbt;
}