#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {int /*<<< orphan*/  rev; void* author; void* date; } ;
typedef  TYPE_2__ revision_info_t ;
typedef  int /*<<< orphan*/  rev ;
struct TYPE_11__ {int /*<<< orphan*/  revision_infos; int /*<<< orphan*/  pool; TYPE_1__* repos; } ;
typedef  TYPE_3__ report_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_9__ {int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 TYPE_2__* apr_hash_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 TYPE_2__* apr_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_fs_revision_proplist2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* svn_string_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static  svn_error_t *
get_revision_info(report_baton_t *b,
                  svn_revnum_t rev,
                  revision_info_t** revision_info,
                  apr_pool_t *scratch_pool)
{
  apr_hash_t *r_props;
  svn_string_t *cdate, *author;
  revision_info_t* info;

  /* Try to find the info in the report's cache */
  info = apr_hash_get(b->revision_infos, &rev, sizeof(rev));
  if (!info)
    {
      /* Info is not available, yet.
         Get all revprops. */
      SVN_ERR(svn_fs_revision_proplist2(&r_props,
                                        b->repos->fs,
                                        rev,
                                        FALSE,
                                        scratch_pool,
                                        scratch_pool));

      /* Extract the committed-date. */
      cdate = svn_hash_gets(r_props, SVN_PROP_REVISION_DATE);

      /* Extract the last-author. */
      author = svn_hash_gets(r_props, SVN_PROP_REVISION_AUTHOR);

      /* Create a result object */
      info = apr_palloc(b->pool, sizeof(*info));
      info->rev = rev;
      info->date = svn_string_dup(cdate, b->pool);
      info->author = svn_string_dup(author, b->pool);

      /* Cache it */
      apr_hash_set(b->revision_infos, &info->rev, sizeof(info->rev), info);
    }

  *revision_info = info;
  return SVN_NO_ERROR;
}