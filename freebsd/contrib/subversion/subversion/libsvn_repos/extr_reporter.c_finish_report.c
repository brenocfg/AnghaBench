#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {int /*<<< orphan*/  edit_baton; TYPE_2__* editor; int /*<<< orphan*/ ** s_roots; int /*<<< orphan*/  t_rev; TYPE_1__* repos; int /*<<< orphan*/  t_root; int /*<<< orphan*/  reader; TYPE_4__* lookahead; int /*<<< orphan*/ * s_operand; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_3__ report_baton_t ;
struct TYPE_12__ {int /*<<< orphan*/  depth; int /*<<< orphan*/  rev; int /*<<< orphan*/  path; scalar_t__ link_path; } ;
typedef  TYPE_4__ path_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* abort_edit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* close_edit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int NUM_CACHED_SOURCE_ROOTS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_REPOS_BAD_REVISION_REPORT ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  drive (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_path_info (TYPE_4__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_spillbuf__reader_write (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
finish_report(report_baton_t *b, apr_pool_t *pool)
{
  path_info_t *info;
  apr_pool_t *subpool;
  svn_revnum_t s_rev;
  int i;

  /* Save our pool to manage the lookahead and fs_root cache with. */
  b->pool = pool;

  /* Add the end marker. */
  SVN_ERR(svn_spillbuf__reader_write(b->reader, "-", 1, pool));

  /* Read the first pathinfo from the report and verify that it is a top-level
     set_path entry. */
  SVN_ERR(read_path_info(&info, b->reader, pool));
  if (!info || strcmp(info->path, b->s_operand) != 0
      || info->link_path || !SVN_IS_VALID_REVNUM(info->rev))
    return svn_error_create(SVN_ERR_REPOS_BAD_REVISION_REPORT, NULL,
                            _("Invalid report for top level of working copy"));
  s_rev = info->rev;

  /* Initialize the lookahead pathinfo. */
  subpool = svn_pool_create(pool);
  SVN_ERR(read_path_info(&b->lookahead, b->reader, subpool));

  if (b->lookahead && strcmp(b->lookahead->path, b->s_operand) == 0)
    {
      /* If the operand of the wc operation is switched or deleted,
         then info above is just a place-holder, and the only thing we
         have to do is pass the revision it contains to open_root.
         The next pathinfo actually describes the target. */
      if (!*b->s_operand)
        return svn_error_create(SVN_ERR_REPOS_BAD_REVISION_REPORT, NULL,
                                _("Two top-level reports with no target"));
      /* If the client issued a set-path followed by a delete-path, we need
         to respect the depth set by the initial set-path. */
      if (! SVN_IS_VALID_REVNUM(b->lookahead->rev))
        {
          b->lookahead->depth = info->depth;
        }
      info = b->lookahead;
      SVN_ERR(read_path_info(&b->lookahead, b->reader, subpool));
    }

  /* Open the target root and initialize the source root cache. */
  SVN_ERR(svn_fs_revision_root(&b->t_root, b->repos->fs, b->t_rev, pool));
  for (i = 0; i < NUM_CACHED_SOURCE_ROOTS; i++)
    b->s_roots[i] = NULL;

  {
    svn_error_t *err = svn_error_trace(drive(b, s_rev, info, pool));

    if (err == SVN_NO_ERROR)
      return svn_error_trace(b->editor->close_edit(b->edit_baton, pool));

    return svn_error_trace(
                svn_error_compose_create(err,
                                         b->editor->abort_edit(b->edit_baton,
                                                               pool)));
  }
}