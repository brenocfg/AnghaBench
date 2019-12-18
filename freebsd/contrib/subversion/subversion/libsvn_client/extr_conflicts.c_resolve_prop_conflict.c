#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_conflict_choice_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_14__ {int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  notify_func2; } ;
typedef  TYPE_3__ svn_client_ctx_t ;
struct TYPE_15__ {int /*<<< orphan*/ * legacy_prop_conflict_propname; int /*<<< orphan*/  prop_conflicts; int /*<<< orphan*/  resolved_props; } ;
typedef  TYPE_4__ svn_client_conflict_t ;
struct TYPE_12__ {char* propname; int /*<<< orphan*/ * merged_propval; } ;
struct TYPE_13__ {TYPE_1__ prop; } ;
struct TYPE_16__ {TYPE_2__ type_data; } ;
typedef  TYPE_5__ svn_client_conflict_option_t ;
typedef  scalar_t__ svn_client_conflict_option_id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_pool_get (int /*<<< orphan*/ ) ; 
 void* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char const* apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  conflict_option_id_to_wc_conflict_choice (scalar_t__) ; 
 char* svn_client_conflict_get_local_abspath (TYPE_4__*) ; 
 scalar_t__ svn_client_conflict_option_get_id (TYPE_5__*) ; 
 scalar_t__ svn_client_conflict_option_merged_text ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,TYPE_5__*) ; 
 int /*<<< orphan*/  svn_io_sleep_for_timestamps (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__acquire_write_lock_for_resolve (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__conflict_prop_mark_resolved (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__release_write_lock (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
resolve_prop_conflict(svn_client_conflict_option_t *option,
                      svn_client_conflict_t *conflict,
                      svn_client_ctx_t *ctx,
                      apr_pool_t *scratch_pool)
{
  svn_client_conflict_option_id_t option_id;
  svn_wc_conflict_choice_t conflict_choice;
  const char *local_abspath;
  const char *lock_abspath;
  const char *propname = option->type_data.prop.propname;
  svn_error_t *err;
  const svn_string_t *merged_value;

  option_id = svn_client_conflict_option_get_id(option);
  conflict_choice = conflict_option_id_to_wc_conflict_choice(option_id);
  local_abspath = svn_client_conflict_get_local_abspath(conflict);

  if (option_id == svn_client_conflict_option_merged_text)
    merged_value = option->type_data.prop.merged_propval;
  else
    merged_value = NULL;

  SVN_ERR(svn_wc__acquire_write_lock_for_resolve(&lock_abspath, ctx->wc_ctx,
                                                 local_abspath,
                                                 scratch_pool, scratch_pool));
  err = svn_wc__conflict_prop_mark_resolved(ctx->wc_ctx, local_abspath,
                                            propname, conflict_choice,
                                            merged_value,
                                            ctx->notify_func2,
                                            ctx->notify_baton2,
                                            scratch_pool);
  err = svn_error_compose_create(err, svn_wc__release_write_lock(ctx->wc_ctx,
                                                                 lock_abspath,
                                                                 scratch_pool));
  svn_io_sleep_for_timestamps(local_abspath, scratch_pool);
  SVN_ERR(err);

  if (propname[0] == '\0')
    {
      apr_hash_index_t *hi;

      /* All properties have been resolved to the same option. */
      for (hi = apr_hash_first(scratch_pool, conflict->prop_conflicts);
           hi;
           hi = apr_hash_next(hi))
        {
          const char *this_propname = apr_hash_this_key(hi);

          svn_hash_sets(conflict->resolved_props,
                        apr_pstrdup(apr_hash_pool_get(conflict->resolved_props),
                                    this_propname),
                        option);
          svn_hash_sets(conflict->prop_conflicts, this_propname, NULL);
        }

      conflict->legacy_prop_conflict_propname = NULL;
    }
  else
    {
      svn_hash_sets(conflict->resolved_props,
                    apr_pstrdup(apr_hash_pool_get(conflict->resolved_props),
                                propname),
                   option);
      svn_hash_sets(conflict->prop_conflicts, propname, NULL);

      if (apr_hash_count(conflict->prop_conflicts) > 0)
        conflict->legacy_prop_conflict_propname =
            apr_hash_this_key(apr_hash_first(scratch_pool,
                                             conflict->prop_conflicts));
      else
        conflict->legacy_prop_conflict_propname = NULL;
    }

  return SVN_NO_ERROR;
}