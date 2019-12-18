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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct parse_baton {scalar_t__ uuid_action; int /*<<< orphan*/  fs; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_fs_set_uuid (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_youngest_rev (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_repos_load_uuid_force ; 
 scalar_t__ svn_repos_load_uuid_ignore ; 

__attribute__((used)) static svn_error_t *
uuid_record(const char *uuid,
            void *parse_baton,
            apr_pool_t *pool)
{
  struct parse_baton *pb = parse_baton;
  svn_revnum_t youngest_rev;

  if (pb->uuid_action == svn_repos_load_uuid_ignore)
    return SVN_NO_ERROR;

  if (pb->uuid_action != svn_repos_load_uuid_force)
    {
      SVN_ERR(svn_fs_youngest_rev(&youngest_rev, pb->fs, pool));
      if (youngest_rev != 0)
        return SVN_NO_ERROR;
    }

  return svn_fs_set_uuid(pb->fs, uuid, pool);
}