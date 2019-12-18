#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_16__ {scalar_t__ kind; } ;
typedef  TYPE_1__ const svn_checksum_t ;
struct file_baton_t {char* temp_file_path; int /*<<< orphan*/ * pool; int /*<<< orphan*/  name; int /*<<< orphan*/  ignoring_ancestry; scalar_t__ repos_only; int /*<<< orphan*/  pfb; int /*<<< orphan*/  right_src; int /*<<< orphan*/  left_src; int /*<<< orphan*/  relpath; int /*<<< orphan*/  local_abspath; TYPE_1__ const* base_checksum; int /*<<< orphan*/  propchanges; int /*<<< orphan*/ * base_props; scalar_t__ added; int /*<<< orphan*/  result_digest; scalar_t__ skip; struct edit_baton_t* eb; struct dir_baton_t* parent_baton; } ;
struct edit_baton_t {scalar_t__ local_before_remote; TYPE_12__* processor; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  db; int /*<<< orphan*/  anchor_abspath; scalar_t__ diff_pristine; } ;
struct dir_baton_t {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* file_changed ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* file_deleted ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN_WC_TRANSLATE_TO_NF ; 
 int SVN_WC_TRANSLATE_USE_GLOBAL_TMP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  handle_local_only (struct dir_baton_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  maybe_done (struct dir_baton_t*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ *) ; 
 TYPE_1__ const* svn_checksum__from_digest_md5 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_match (TYPE_1__ const*,TYPE_1__ const*) ; 
 scalar_t__ svn_checksum_md5 ; 
 int /*<<< orphan*/ * svn_checksum_mismatch_err (TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (TYPE_1__ const**,scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_prop__patch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_diffs (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_get_md5 (TYPE_1__ const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_get_path (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_pristine_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_props (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__internal_translated_file (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
close_file(void *file_baton,
           const char *expected_md5_digest,
           apr_pool_t *pool)
{
  struct file_baton_t *fb = file_baton;
  struct dir_baton_t *pb = fb->parent_baton;
  struct edit_baton_t *eb = fb->eb;
  apr_pool_t *scratch_pool = fb->pool;

  /* The repository information; constructed from BASE + Changes */
  const char *repos_file;
  apr_hash_t *repos_props;

  if (fb->skip)
    {
      svn_pool_destroy(fb->pool); /* destroys scratch_pool and fb */
      SVN_ERR(maybe_done(pb));
      return SVN_NO_ERROR;
    }

  if (expected_md5_digest != NULL)
    {
      svn_checksum_t *expected_checksum;
      const svn_checksum_t *result_checksum;

      if (fb->temp_file_path)
        result_checksum = svn_checksum__from_digest_md5(fb->result_digest,
                                                        scratch_pool);
      else
        result_checksum = fb->base_checksum;

      SVN_ERR(svn_checksum_parse_hex(&expected_checksum, svn_checksum_md5,
                                     expected_md5_digest, scratch_pool));

      if (result_checksum->kind != svn_checksum_md5)
        SVN_ERR(svn_wc__db_pristine_get_md5(&result_checksum,
                                            eb->db, fb->local_abspath,
                                            result_checksum,
                                            scratch_pool, scratch_pool));

      if (!svn_checksum_match(expected_checksum, result_checksum))
        return svn_checksum_mismatch_err(
                            expected_checksum,
                            result_checksum,
                            pool,
                            _("Checksum mismatch for '%s'"),
                            svn_dirent_local_style(fb->local_abspath,
                                                   scratch_pool));
    }

  if (eb->local_before_remote && !fb->repos_only && !fb->ignoring_ancestry)
    SVN_ERR(handle_local_only(pb, fb->name, scratch_pool));

  {
    apr_hash_t *prop_base;

    if (fb->added)
      prop_base = apr_hash_make(scratch_pool);
    else
      prop_base = fb->base_props;

    /* includes entry props */
    repos_props = svn_prop__patch(prop_base, fb->propchanges, scratch_pool);

    repos_file = fb->temp_file_path;
    if (! repos_file)
      {
        assert(fb->base_checksum);
        SVN_ERR(svn_wc__db_pristine_get_path(&repos_file,
                                             eb->db, eb->anchor_abspath,
                                             fb->base_checksum,
                                             scratch_pool, scratch_pool));
      }
  }

  if (fb->repos_only)
    {
      SVN_ERR(eb->processor->file_deleted(fb->relpath,
                                          fb->left_src,
                                          fb->temp_file_path,
                                          repos_props,
                                          fb->pfb,
                                          eb->processor,
                                          scratch_pool));
    }
  else
    {
      /* Produce a diff of actual or pristine against repos */
      apr_hash_t *local_props;
      apr_array_header_t *prop_changes;
      const char *localfile;

      /* pb->local_info contains some information that might allow optimizing
         this a bit */

      if (eb->diff_pristine)
        {
          const svn_checksum_t *checksum;
          SVN_ERR(svn_wc__db_read_pristine_info(NULL, NULL, NULL, NULL, NULL,
                                                NULL, &checksum, NULL, NULL,
                                                &local_props,
                                                eb->db, fb->local_abspath,
                                                scratch_pool, scratch_pool));
          assert(checksum);
          SVN_ERR(svn_wc__db_pristine_get_path(&localfile,
                                               eb->db, eb->anchor_abspath,
                                               checksum,
                                               scratch_pool, scratch_pool));
        }
      else
        {
          SVN_ERR(svn_wc__db_read_props(&local_props,
                                        eb->db, fb->local_abspath,
                                        scratch_pool, scratch_pool));

          /* a detranslated version of the working file */
          SVN_ERR(svn_wc__internal_translated_file(
                    &localfile, fb->local_abspath, eb->db, fb->local_abspath,
                    SVN_WC_TRANSLATE_TO_NF | SVN_WC_TRANSLATE_USE_GLOBAL_TMP,
                    eb->cancel_func, eb->cancel_baton,
                    scratch_pool, scratch_pool));
        }

      SVN_ERR(svn_prop_diffs(&prop_changes, local_props, repos_props,
                             scratch_pool));


      /* ### as a good diff processor we should now only report changes, and
             report file_closed() in other cases */
      SVN_ERR(eb->processor->file_changed(fb->relpath,
                                          fb->left_src,
                                          fb->right_src,
                                          repos_file /* left file */,
                                          localfile /* right file */,
                                          repos_props /* left_props */,
                                          local_props /* right props */,
                                          TRUE /* ### file_modified */,
                                          prop_changes,
                                          fb->pfb,
                                          eb->processor,
                                          scratch_pool));
    }

  if (!eb->local_before_remote && !fb->repos_only && !fb->ignoring_ancestry)
    SVN_ERR(handle_local_only(pb, fb->name, scratch_pool));

  svn_pool_destroy(fb->pool); /* destroys scratch_pool and fb */
  SVN_ERR(maybe_done(pb));
  return SVN_NO_ERROR;
}