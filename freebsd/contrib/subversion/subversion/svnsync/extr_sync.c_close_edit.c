#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  wrapped_edit_baton; TYPE_1__* wrapped_editor; scalar_t__ svnmerge_blocked; scalar_t__ svnmerge_migrated; scalar_t__ mergeinfo_stripped; scalar_t__ mergeinfo_tweaked; scalar_t__ got_textdeltas; int /*<<< orphan*/  quiet; int /*<<< orphan*/  base_revision; int /*<<< orphan*/  called_open_root; } ;
typedef  TYPE_2__ edit_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/ * (* close_edit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* close_directory ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* open_root ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static svn_error_t *
close_edit(void *edit_baton,
           apr_pool_t *pool)
{
  edit_baton_t *eb = edit_baton;

  /* If we haven't opened the root yet, that means we're transfering
     an empty revision, probably because we aren't allowed to see the
     contents for some reason.  In any event, we need to open the root
     and close it again, before we can close out the edit, or the
     commit will fail. */

  if (! eb->called_open_root)
    {
      void *baton;
      SVN_ERR(eb->wrapped_editor->open_root(eb->wrapped_edit_baton,
                                            eb->base_revision, pool,
                                            &baton));
      SVN_ERR(eb->wrapped_editor->close_directory(baton, pool));
    }

  if (! eb->quiet)
    {
      if (eb->got_textdeltas)
        SVN_ERR(svn_cmdline_printf(pool, "\n"));
      if (eb->mergeinfo_tweaked)
        SVN_ERR(svn_cmdline_printf(pool,
                                   "NOTE: Adjusted Subversion mergeinfo in "
                                   "this revision.\n"));
      if (eb->mergeinfo_stripped)
        SVN_ERR(svn_cmdline_printf(pool,
                                   "NOTE: Dropped Subversion mergeinfo "
                                   "from this revision.\n"));
      if (eb->svnmerge_migrated)
        SVN_ERR(svn_cmdline_printf(pool,
                                   "NOTE: Migrated 'svnmerge-integrated' in "
                                   "this revision.\n"));
      if (eb->svnmerge_blocked)
        SVN_ERR(svn_cmdline_printf(pool,
                                   "NOTE: Saw 'svnmerge-blocked' in this "
                                   "revision (but didn't migrate it).\n"));
    }

  return eb->wrapped_editor->close_edit(eb->wrapped_edit_baton, pool);
}