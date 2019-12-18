#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* file_added ) (char const*,TYPE_2__*,TYPE_2__*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* file_opened ) (void**,int*,char const*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,void*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_diff_tree_processor_t ;
struct TYPE_12__ {char const* repos_relpath; char const* moved_from_relpath; } ;
typedef  TYPE_2__ svn_diff_source_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN_WC_TRANSLATE_TO_NF ; 
 int SVN_WC_TRANSLATE_USE_GLOBAL_TMP ; 
 int TRUE ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (void**,int*,char const*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,void*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (char const*,TYPE_2__*,TYPE_2__*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_diff__source_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/ * svn_prop_hash_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_get_path (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_pristine_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_pristine_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_deleted ; 
 scalar_t__ svn_wc__db_status_normal ; 
 int /*<<< orphan*/  svn_wc__internal_file_modified_p (int*,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__internal_translated_file (char const**,char const*,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__diff_local_only_file(svn_wc__db_t *db,
                             const char *local_abspath,
                             const char *relpath,
                             const char *moved_from_relpath,
                             const svn_diff_tree_processor_t *processor,
                             void *processor_parent_baton,
                             svn_boolean_t diff_pristine,
                             svn_cancel_func_t cancel_func,
                             void *cancel_baton,
                             apr_pool_t *scratch_pool)
{
  svn_diff_source_t *right_src;
  svn_diff_source_t *copyfrom_src = NULL;
  svn_wc__db_status_t status;
  svn_node_kind_t kind;
  const svn_checksum_t *checksum;
  const char *original_repos_relpath;
  svn_revnum_t original_revision;
  svn_boolean_t had_props;
  svn_boolean_t props_mod;
  apr_hash_t *pristine_props;
  apr_hash_t *right_props = NULL;
  const char *pristine_file;
  const char *translated_file;
  svn_revnum_t revision;
  void *file_baton = NULL;
  svn_boolean_t skip = FALSE;
  svn_boolean_t file_mod = TRUE;

  SVN_ERR(svn_wc__db_read_info(&status, &kind, &revision, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, &checksum, NULL,
                               &original_repos_relpath, NULL, NULL,
                               &original_revision, NULL, NULL, NULL,
                               NULL, NULL, NULL, &had_props,
                               &props_mod, NULL, NULL, NULL,
                               db, local_abspath,
                               scratch_pool, scratch_pool));

  assert(kind == svn_node_file
         && (status == svn_wc__db_status_normal
             || status == svn_wc__db_status_added
             || (status == svn_wc__db_status_deleted && diff_pristine)));


  if (status == svn_wc__db_status_deleted)
    {
      assert(diff_pristine);

      SVN_ERR(svn_wc__db_read_pristine_info(&status, &kind, NULL, NULL, NULL,
                                            NULL, &checksum, NULL, &had_props,
                                            &pristine_props,
                                            db, local_abspath,
                                            scratch_pool, scratch_pool));
      props_mod = FALSE;
    }
  else if (!had_props)
    pristine_props = apr_hash_make(scratch_pool);
  else
    SVN_ERR(svn_wc__db_read_pristine_props(&pristine_props,
                                           db, local_abspath,
                                           scratch_pool, scratch_pool));

  if (original_repos_relpath)
    {
      copyfrom_src = svn_diff__source_create(original_revision, scratch_pool);
      copyfrom_src->repos_relpath = original_repos_relpath;
      copyfrom_src->moved_from_relpath = moved_from_relpath;
    }

  if (props_mod || !SVN_IS_VALID_REVNUM(revision))
    right_src = svn_diff__source_create(SVN_INVALID_REVNUM, scratch_pool);
  else
    {
      if (diff_pristine)
        file_mod = FALSE;
      else
        SVN_ERR(svn_wc__internal_file_modified_p(&file_mod, db, local_abspath,
                                                 FALSE, scratch_pool));

      if (!file_mod)
        right_src = svn_diff__source_create(revision, scratch_pool);
      else
        right_src = svn_diff__source_create(SVN_INVALID_REVNUM, scratch_pool);
    }

  SVN_ERR(processor->file_opened(&file_baton, &skip,
                                 relpath,
                                 NULL /* left_source */,
                                 right_src,
                                 copyfrom_src,
                                 processor_parent_baton,
                                 processor,
                                 scratch_pool, scratch_pool));

  if (skip)
    return SVN_NO_ERROR;

  if (props_mod && !diff_pristine)
    SVN_ERR(svn_wc__db_read_props(&right_props, db, local_abspath,
                                  scratch_pool, scratch_pool));
  else
    right_props = svn_prop_hash_dup(pristine_props, scratch_pool);

  if (checksum)
    SVN_ERR(svn_wc__db_pristine_get_path(&pristine_file, db, local_abspath,
                                         checksum, scratch_pool, scratch_pool));
  else
    pristine_file = NULL;

  if (diff_pristine)
    {
      translated_file = pristine_file; /* No translation needed */
    }
  else
    {
      SVN_ERR(svn_wc__internal_translated_file(
           &translated_file, local_abspath, db, local_abspath,
           SVN_WC_TRANSLATE_TO_NF | SVN_WC_TRANSLATE_USE_GLOBAL_TMP,
           cancel_func, cancel_baton,
           scratch_pool, scratch_pool));
    }

  SVN_ERR(processor->file_added(relpath,
                                copyfrom_src,
                                right_src,
                                copyfrom_src
                                  ? pristine_file
                                  : NULL,
                                translated_file,
                                copyfrom_src
                                  ? pristine_props
                                  : NULL,
                                right_props,
                                file_baton,
                                processor,
                                scratch_pool));

  return SVN_NO_ERROR;
}