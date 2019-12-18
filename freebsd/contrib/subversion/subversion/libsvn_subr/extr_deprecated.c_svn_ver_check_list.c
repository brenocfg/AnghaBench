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
typedef  int /*<<< orphan*/  svn_version_t ;
typedef  int /*<<< orphan*/  svn_version_checklist_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_ver_check_list2 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ver_compatible ; 

svn_error_t *
svn_ver_check_list(const svn_version_t *my_version,
                   const svn_version_checklist_t *checklist)
{
  return svn_ver_check_list2(my_version, checklist, svn_ver_compatible);
}