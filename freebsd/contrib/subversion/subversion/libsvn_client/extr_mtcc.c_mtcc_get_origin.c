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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  base_revision; int /*<<< orphan*/  root_op; } ;
typedef  TYPE_1__ svn_client__mtcc_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  get_origin (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static svn_error_t *
mtcc_get_origin(const char **origin_relpath,
                svn_revnum_t *rev,
                const char *relpath,
                svn_boolean_t ignore_enoent,
                svn_client__mtcc_t *mtcc,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  svn_boolean_t done = FALSE;

  *origin_relpath = NULL;
  *rev = SVN_INVALID_REVNUM;

  SVN_ERR(get_origin(&done, origin_relpath, rev, mtcc->root_op, relpath,
                     result_pool, scratch_pool));

  if (!*origin_relpath && !done)
    {
      *origin_relpath = apr_pstrdup(result_pool, relpath);
      *rev = mtcc->base_revision;
    }
  else if (!ignore_enoent)
    {
      return svn_error_createf(SVN_ERR_FS_NOT_FOUND, NULL,
                               _("No origin found for node at '%s'"),
                               relpath);
    }

  return SVN_NO_ERROR;
}