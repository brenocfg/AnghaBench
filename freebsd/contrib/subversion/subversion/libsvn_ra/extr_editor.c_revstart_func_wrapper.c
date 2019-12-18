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
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct wrapped_replay_baton_t {int /*<<< orphan*/  cb_baton; int /*<<< orphan*/  editor; int /*<<< orphan*/  provide_props_cb; int /*<<< orphan*/  session; int /*<<< orphan*/  replay_baton; int /*<<< orphan*/  (* revstart_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct svn_delta__extra_baton {int dummy; } ;
struct fp_baton {int /*<<< orphan*/  cb_baton; int /*<<< orphan*/  provide_props_cb; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct fp_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fetch_base ; 
 int /*<<< orphan*/  fetch_props ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_delta__delta_from_editor (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct svn_delta__extra_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_repos_root2 (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_session_url (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 
 char* svn_uri_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
revstart_func_wrapper(svn_revnum_t revision,
                      void *replay_baton,
                      const svn_delta_editor_t **deditor,
                      void **dedit_baton,
                      apr_hash_t *rev_props,
                      apr_pool_t *result_pool)
{
  struct wrapped_replay_baton_t *wrb = replay_baton;
  const char *repos_root;
  const char *session_url;
  const char *base_relpath;
  svn_boolean_t *found_abs_paths;
  struct fp_baton *fpb;
  struct svn_delta__extra_baton *exb;

  /* Get the Ev2 editor from the original revstart func. */
  SVN_ERR(wrb->revstart_func(revision, wrb->replay_baton, &wrb->editor,
                             rev_props, result_pool));

  /* Get or calculate the appropriate repos root and base relpath. */
  SVN_ERR(svn_ra_get_repos_root2(wrb->session, &repos_root, result_pool));
  SVN_ERR(svn_ra_get_session_url(wrb->session, &session_url, result_pool));
  base_relpath = svn_uri_skip_ancestor(repos_root, session_url, result_pool);

  /* We will assume that when the underlying Ev1 editor is finally driven
     by the shim, that we will not need to prepend "/" to the paths. Place
     this on the heap because it is examined much later. Set to FALSE.  */
  found_abs_paths = apr_pcalloc(result_pool, sizeof(*found_abs_paths));

  /* The PROVIDE_PROPS_CB callback does not match what the shims want.
     Let's jigger things around a little bit here.  */
  fpb = apr_palloc(result_pool, sizeof(*fpb));
  fpb->provide_props_cb = wrb->provide_props_cb;
  fpb->cb_baton = wrb->cb_baton;

  /* Create the extra baton. */
  exb = apr_pcalloc(result_pool, sizeof(*exb));

  /* Create the Ev1 editor from the Ev2 editor provided by the RA layer.

     Note: GET_COPYSRC_KIND_CB is compatible in type/semantics with the
     shim's FETCH_KIND_FUNC parameter.  */
  SVN_ERR(svn_delta__delta_from_editor(deditor, dedit_baton, wrb->editor,
                                       NULL, NULL,
                                       found_abs_paths,
                                       repos_root, base_relpath,
                                       fetch_props, wrb->cb_baton,
                                       fetch_base, wrb->cb_baton,
                                       exb, result_pool));

  return SVN_NO_ERROR;
}