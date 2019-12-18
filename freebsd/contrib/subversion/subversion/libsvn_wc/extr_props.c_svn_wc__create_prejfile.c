#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_operation_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_17__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_18__ {struct TYPE_18__* next; TYPE_1__* children; } ;
typedef  TYPE_3__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_16__ {TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  prop_conflict_from_skel (TYPE_2__ const**,TYPE_3__ const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prop_conflict_new (TYPE_2__ const**,char const*,TYPE_2__ const*,TYPE_2__ const*,TYPE_2__ const*,TYPE_2__ const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__conflict_read_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_read_prop_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_conflict (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_pristine_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_temp_wcroot_tempdir (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_operation_merge ; 

svn_error_t *
svn_wc__create_prejfile(const char **tmp_prejfile_abspath,
                        svn_wc__db_t *db,
                        const char *local_abspath,
                        const svn_skel_t *prop_conflict_data,
                        svn_cancel_func_t cancel_func,
                        void *cancel_baton,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  const char *tempdir_abspath;
  svn_stream_t *stream;
  const char *temp_abspath;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  const svn_skel_t *scan;

  SVN_ERR(svn_wc__db_temp_wcroot_tempdir(&tempdir_abspath,
                                         db, local_abspath,
                                         iterpool, iterpool));

  SVN_ERR(svn_stream_open_unique(&stream, &temp_abspath,
                                 tempdir_abspath, svn_io_file_del_none,
                                 scratch_pool, iterpool));

  if (prop_conflict_data)
    {
      for (scan = prop_conflict_data->children->next;
            scan != NULL; scan = scan->next)
        {
          const svn_string_t *conflict_desc;

          svn_pool_clear(iterpool);

          SVN_ERR(prop_conflict_from_skel(&conflict_desc, scan,
                                          cancel_func, cancel_baton,
                                          iterpool, iterpool));

          SVN_ERR(svn_stream_puts(stream, conflict_desc->data));
        }
    }
  else
    {
      svn_wc_operation_t operation;
      apr_hash_index_t *hi;
      apr_hash_t *old_props;
      apr_hash_t *mine_props;
      apr_hash_t *their_original_props;
      apr_hash_t *their_props;
      apr_hash_t *conflicted_props;
      svn_skel_t *conflicts;

      SVN_ERR(svn_wc__db_read_conflict(&conflicts, NULL, NULL,
                                       db, local_abspath,
                                      scratch_pool, scratch_pool));

      SVN_ERR(svn_wc__conflict_read_info(&operation, NULL, NULL, NULL, NULL,
                                         db, local_abspath,
                                         conflicts,
                                         scratch_pool, scratch_pool));

      SVN_ERR(svn_wc__conflict_read_prop_conflict(NULL,
                                                  &mine_props,
                                                  &their_original_props,
                                                  &their_props,
                                                  &conflicted_props,
                                                  db, local_abspath,
                                                  conflicts,
                                                  scratch_pool,
                                                  scratch_pool));

      if (operation == svn_wc_operation_merge)
        SVN_ERR(svn_wc__db_read_pristine_props(&old_props, db, local_abspath,
                                                scratch_pool, scratch_pool));
      else
        old_props = their_original_props;

      /* ### TODO: Sort conflicts? */
      for (hi = apr_hash_first(scratch_pool, conflicted_props);
           hi;
           hi = apr_hash_next(hi))
        {
          const svn_string_t *conflict_desc;
          const char *propname = apr_hash_this_key(hi);
          const svn_string_t *old_value;
          const svn_string_t *mine_value;
          const svn_string_t *their_value;
          const svn_string_t *their_original_value;

          svn_pool_clear(iterpool);

          old_value = old_props ? svn_hash_gets(old_props, propname) : NULL;
          mine_value = mine_props ? svn_hash_gets(mine_props, propname) : NULL;
          their_value = their_props ? svn_hash_gets(their_props, propname)
                                    : NULL;
          their_original_value = their_original_props
                                    ? svn_hash_gets(their_original_props, propname)
                                    : NULL;

          SVN_ERR(prop_conflict_new(&conflict_desc,
                                    propname, old_value, mine_value,
                                    their_value, their_original_value,
                                    cancel_func, cancel_baton,
                                    iterpool, iterpool));

          SVN_ERR(svn_stream_puts(stream, conflict_desc->data));
        }
    }

  SVN_ERR(svn_stream_close(stream));

  svn_pool_destroy(iterpool);

  *tmp_prejfile_abspath = apr_pstrdup(result_pool, temp_abspath);
  return SVN_NO_ERROR;
}