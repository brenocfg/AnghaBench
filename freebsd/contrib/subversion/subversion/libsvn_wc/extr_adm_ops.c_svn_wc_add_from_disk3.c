#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  mime_type; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (void*,TYPE_1__*,int /*<<< orphan*/ *) ;
struct TYPE_9__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_3__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MIME_TYPE ; 
 int /*<<< orphan*/  add_from_disk (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_can_add_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_can_add_to_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_get_value (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__canonicalize_props (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_add ; 

svn_error_t *
svn_wc_add_from_disk3(svn_wc_context_t *wc_ctx,
                      const char *local_abspath,
                      const apr_hash_t *props,
                      svn_boolean_t skip_checks,
                      svn_wc_notify_func2_t notify_func,
                      void *notify_baton,
                      apr_pool_t *scratch_pool)
{
  svn_node_kind_t kind;

  SVN_ERR(check_can_add_node(&kind, NULL, NULL, wc_ctx->db, local_abspath,
                             NULL, SVN_INVALID_REVNUM, scratch_pool));
  SVN_ERR(check_can_add_to_parent(NULL, NULL, wc_ctx->db, local_abspath,
                                  scratch_pool, scratch_pool));

  /* Canonicalize and check the props */
  if (props)
    {
      apr_hash_t *new_props;

      SVN_ERR(svn_wc__canonicalize_props(
                &new_props,
                local_abspath, kind, props, skip_checks,
                scratch_pool, scratch_pool));
      props = new_props;
    }

  /* Add to the DB and maybe update on-disk executable read-only bits */
  SVN_ERR(add_from_disk(wc_ctx->db, local_abspath, kind, props,
                        scratch_pool));

  /* Report the addition to the caller. */
  if (notify_func != NULL)
    {
      svn_wc_notify_t *notify = svn_wc_create_notify(local_abspath,
                                                     svn_wc_notify_add,
                                                     scratch_pool);
      notify->kind = kind;
      notify->mime_type = svn_prop_get_value(props, SVN_PROP_MIME_TYPE);
      (*notify_func)(notify_baton, notify, scratch_pool);
    }

  return SVN_NO_ERROR;
}