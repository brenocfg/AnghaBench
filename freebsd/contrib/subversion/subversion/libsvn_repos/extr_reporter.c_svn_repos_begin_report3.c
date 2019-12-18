#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_5__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  int /*<<< orphan*/  svn_repos_authz_func_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  void* svn_boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  reader; int /*<<< orphan*/ * pool; int /*<<< orphan*/  revision_infos; void* authz_read_baton; int /*<<< orphan*/  authz_read_func; void* edit_baton; int /*<<< orphan*/  const* editor; int /*<<< orphan*/  is_switch; void* send_copyfrom_args; void* ignore_ancestry; scalar_t__ requested_depth; int /*<<< orphan*/  zero_copy_limit; void* text_deltas; void* fs_base; void* t_path; int /*<<< orphan*/  t_rev; int /*<<< orphan*/  s_operand; TYPE_1__* repos; } ;
typedef  TYPE_2__ report_baton_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_REPOS_BAD_ARGS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_2__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ svn_depth_exclude ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_get_uuid (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 
 void* svn_fspath__canonicalize (char const*,int /*<<< orphan*/ *) ; 
 void* svn_fspath__join (void*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_spillbuf__reader_create (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_create (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_begin_report3(void **report_baton,
                        svn_revnum_t revnum,
                        svn_repos_t *repos,
                        const char *fs_base,
                        const char *s_operand,
                        const char *switch_path,
                        svn_boolean_t text_deltas,
                        svn_depth_t depth,
                        svn_boolean_t ignore_ancestry,
                        svn_boolean_t send_copyfrom_args,
                        const svn_delta_editor_t *editor,
                        void *edit_baton,
                        svn_repos_authz_func_t authz_read_func,
                        void *authz_read_baton,
                        apr_size_t zero_copy_limit,
                        apr_pool_t *pool)
{
  report_baton_t *b;
  const char *uuid;

  if (depth == svn_depth_exclude)
    return svn_error_create(SVN_ERR_REPOS_BAD_ARGS, NULL,
                            _("Request depth 'exclude' not supported"));

  SVN_ERR(svn_fs_get_uuid(repos->fs, &uuid, pool));

  /* Build a reporter baton.  Copy strings in case the caller doesn't
     keep track of them. */
  b = apr_palloc(pool, sizeof(*b));
  b->repos = repos;
  b->fs_base = svn_fspath__canonicalize(fs_base, pool);
  b->s_operand = apr_pstrdup(pool, s_operand);
  b->t_rev = revnum;
  b->t_path = switch_path ? svn_fspath__canonicalize(switch_path, pool)
                          : svn_fspath__join(b->fs_base, s_operand, pool);
  b->text_deltas = text_deltas;
  b->zero_copy_limit = zero_copy_limit;
  b->requested_depth = depth;
  b->ignore_ancestry = ignore_ancestry;
  b->send_copyfrom_args = send_copyfrom_args;
  b->is_switch = (switch_path != NULL);
  b->editor = editor;
  b->edit_baton = edit_baton;
  b->authz_read_func = authz_read_func;
  b->authz_read_baton = authz_read_baton;
  b->revision_infos = apr_hash_make(pool);
  b->pool = pool;
  b->reader = svn_spillbuf__reader_create(1000 /* blocksize */,
                                          1000000 /* maxsize */,
                                          pool);
  b->repos_uuid = svn_string_create(uuid, pool);

  /* Hand reporter back to client. */
  *report_baton = b;
  return SVN_NO_ERROR;
}