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
struct TYPE_3__ {int /*<<< orphan*/  (* close_edit ) (void*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_delta_editor_t ;
struct replay_baton {int /*<<< orphan*/  quiet; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
replay_revend(svn_revnum_t revision,
              void *replay_baton,
              const svn_delta_editor_t *editor,
              void *edit_baton,
              apr_hash_t *rev_props,
              apr_pool_t *pool)
{
  /* No resources left to free. */
  struct replay_baton *rb = replay_baton;

  SVN_ERR(editor->close_edit(edit_baton, pool));

  if (! rb->quiet)
    SVN_ERR(svn_cmdline_fprintf(stderr, pool, "* Dumped revision %lu.\n",
                                revision));
  return SVN_NO_ERROR;
}