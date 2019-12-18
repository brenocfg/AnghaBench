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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
struct replay_baton {int /*<<< orphan*/  extra_ra_session; int /*<<< orphan*/  stdout_stream; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check_cancel ; 
 int /*<<< orphan*/  svn_rdump__get_dump_editor (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rdump__normalize_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__dump_revision_record (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
replay_revstart(svn_revnum_t revision,
                void *replay_baton,
                const svn_delta_editor_t **editor,
                void **edit_baton,
                apr_hash_t *rev_props,
                apr_pool_t *pool)
{
  struct replay_baton *rb = replay_baton;
  apr_hash_t *normal_props;

  /* Normalize and dump the revprops */
  SVN_ERR(svn_rdump__normalize_props(&normal_props, rev_props, pool));
  SVN_ERR(svn_repos__dump_revision_record(rb->stdout_stream, revision, NULL,
                                          normal_props,
                                          TRUE /*props_section_always*/,
                                          pool));

  SVN_ERR(svn_rdump__get_dump_editor(editor, edit_baton, revision,
                                     rb->stdout_stream, rb->extra_ra_session,
                                     NULL, check_cancel, NULL, pool));

  return SVN_NO_ERROR;
}