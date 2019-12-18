#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* member_0; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ svn_version_checklist_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_VERSION_DEFINE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_version ; 
#define  svn_client_version 132 
#define  svn_delta_version 131 
#define  svn_ra_version 130 
#define  svn_subr_version 129 
 int /*<<< orphan*/ * svn_ver_check_list2 (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ver_equal ; 
#define  svn_wc_version 128 

__attribute__((used)) static svn_error_t *
check_lib_versions(void)
{
  static const svn_version_checklist_t checklist[] =
    {
      { "svn_subr",   svn_subr_version },
      { "svn_client", svn_client_version },
      { "svn_wc",     svn_wc_version },
      { "svn_ra",     svn_ra_version },
      { "svn_delta",  svn_delta_version },
      { NULL, NULL }
    };
  SVN_VERSION_DEFINE(my_version);

  return svn_ver_check_list2(&my_version, checklist, svn_ver_equal);
}