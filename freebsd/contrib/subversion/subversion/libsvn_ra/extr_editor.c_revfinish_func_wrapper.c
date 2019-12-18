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
struct wrapped_replay_baton_t {int /*<<< orphan*/  editor; int /*<<< orphan*/  (* revfinish_func ) (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
revfinish_func_wrapper(svn_revnum_t revision,
                       void *replay_baton,
                       const svn_delta_editor_t *editor,
                       void *edit_baton,
                       apr_hash_t *rev_props,
                       apr_pool_t *pool)
{
  struct wrapped_replay_baton_t *wrb = replay_baton;

  SVN_ERR(wrb->revfinish_func(revision, replay_baton, wrb->editor, rev_props,
                              pool));

  return SVN_NO_ERROR;
}