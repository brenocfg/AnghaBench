#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {TYPE_1__* src_right_version; TYPE_2__* src_left_version; } ;
struct TYPE_5__ {char* repos_url; char* repos_uuid; } ;
struct TYPE_4__ {char* repos_url; char* repos_uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_3__* get_conflict_desc2_t (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_conflict_get_repos_info(const char **repos_root_url,
                                   const char **repos_uuid,
                                   svn_client_conflict_t *conflict,
                                   apr_pool_t *result_pool,
                                   apr_pool_t *scratch_pool)
{
  if (repos_root_url)
    {
      if (get_conflict_desc2_t(conflict)->src_left_version)
        *repos_root_url =
          get_conflict_desc2_t(conflict)->src_left_version->repos_url;
      else if (get_conflict_desc2_t(conflict)->src_right_version)
        *repos_root_url =
          get_conflict_desc2_t(conflict)->src_right_version->repos_url;
      else
        *repos_root_url = NULL;
    }

  if (repos_uuid)
    {
      if (get_conflict_desc2_t(conflict)->src_left_version)
        *repos_uuid =
          get_conflict_desc2_t(conflict)->src_left_version->repos_uuid;
      else if (get_conflict_desc2_t(conflict)->src_right_version)
        *repos_uuid =
          get_conflict_desc2_t(conflict)->src_right_version->repos_uuid;
      else
        *repos_uuid = NULL;
    }

  return SVN_NO_ERROR;
}