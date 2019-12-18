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
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct file_baton {scalar_t__ new_text_base_sha1_checksum; int /*<<< orphan*/  local_abspath; int /*<<< orphan*/  propchanges; int /*<<< orphan*/  old_revision; int /*<<< orphan*/ * original_checksum; scalar_t__ add_existed; scalar_t__ adding_file; int /*<<< orphan*/  edit_obstructed; int /*<<< orphan*/  obstruction_found; int /*<<< orphan*/  shadowed; struct dir_baton* dir_baton; struct edit_baton* edit_baton; } ;
struct edit_baton {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  db; int /*<<< orphan*/  diff3_cmd; int /*<<< orphan*/ * target_revision; int /*<<< orphan*/  ext_patterns; } ;
struct dir_baton {int /*<<< orphan*/  local_abspath; } ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN_WC_TRANSLATE_NO_OUTPUT_CLEANUP ; 
 int SVN_WC_TRANSLATE_TO_NF ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  svn_wc__get_translate_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__has_magic_property (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__internal_file_modified_p (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__internal_translated_file (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__perform_file_merge (int /*<<< orphan*/ **,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_state_changed ; 
 int /*<<< orphan*/  svn_wc_notify_state_conflicted ; 
 int /*<<< orphan*/  svn_wc_notify_state_merged ; 
 int /*<<< orphan*/  svn_wc_notify_state_unchanged ; 

__attribute__((used)) static svn_error_t *
merge_file(svn_skel_t **work_items,
           svn_skel_t **conflict_skel,
           svn_boolean_t *install_pristine,
           const char **install_from,
           svn_wc_notify_state_t *content_state,
           struct file_baton *fb,
           apr_hash_t *actual_props,
           apr_time_t last_changed_date,
           apr_pool_t *result_pool,
           apr_pool_t *scratch_pool)
{
  struct edit_baton *eb = fb->edit_baton;
  struct dir_baton *pb = fb->dir_baton;
  svn_boolean_t is_locally_modified;
  svn_boolean_t found_text_conflict = FALSE;

  SVN_ERR_ASSERT(! fb->shadowed
                 && ! fb->obstruction_found
                 && ! fb->edit_obstructed);

  /*
     When this function is called on file F, we assume the following
     things are true:

         - The new pristine text of F is present in the pristine store
           iff FB->NEW_TEXT_BASE_SHA1_CHECKSUM is not NULL.

         - The WC metadata still reflects the old version of F.
           (We can still access the old pristine base text of F.)

     The goal is to update the local working copy of F to reflect
     the changes received from the repository, preserving any local
     modifications.
  */

  *work_items = NULL;
  *install_pristine = FALSE;
  *install_from = NULL;

  /* Start by splitting the file path, getting an access baton for the parent,
     and an entry for the file if any. */

  /* Has the user made local mods to the working file?
     Note that this compares to the current pristine file, which is
     different from fb->old_text_base_path if we have a replaced-with-history
     file.  However, in the case we had an obstruction, we check against the
     new text base.
   */
  if (fb->adding_file && !fb->add_existed)
    {
      is_locally_modified = FALSE; /* There is no file: Don't check */
    }
  else
    {
      /* The working file is not an obstruction.
         So: is the file modified, relative to its ORIGINAL pristine?

         This function sets is_locally_modified to FALSE for
         files that do not exist and for directories. */

      SVN_ERR(svn_wc__internal_file_modified_p(&is_locally_modified,
                                               eb->db, fb->local_abspath,
                                               FALSE /* exact_comparison */,
                                               scratch_pool));
    }

  /* For 'textual' merging, we use the following system:

     When a file is modified and we have a new BASE:
      - For text files
          * svn_wc_merge uses diff3
          * possibly makes backups and marks files as conflicted.

      - For binary files
          * svn_wc_merge makes backups and marks files as conflicted.

     If a file is not modified and we have a new BASE:
       * Install from pristine.

     If we have property changes related to magic properties or if the
     svn:keywords property is set:
       * Retranslate from the working file.
   */
  if (! is_locally_modified
      && fb->new_text_base_sha1_checksum)
    {
          /* If there are no local mods, who cares whether it's a text
             or binary file!  Just write a log command to overwrite
             any working file with the new text-base.  If newline
             conversion or keyword substitution is activated, this
             will happen as well during the copy.
             For replaced files, though, we want to merge in the changes
             even if the file is not modified compared to the (non-revert)
             text-base. */

      *install_pristine = TRUE;
    }
  else if (fb->new_text_base_sha1_checksum)
    {
      /* Actual file exists and has local mods:
         Now we need to let loose svn_wc__merge_internal() to merge
         the textual changes into the working file. */
      SVN_ERR(svn_wc__perform_file_merge(work_items,
                                         conflict_skel,
                                         &found_text_conflict,
                                         eb->db,
                                         fb->local_abspath,
                                         pb->local_abspath,
                                         fb->new_text_base_sha1_checksum,
                                         fb->add_existed
                                                  ? NULL
                                                  : fb->original_checksum,
                                         actual_props,
                                         eb->ext_patterns,
                                         fb->old_revision,
                                         *eb->target_revision,
                                         fb->propchanges,
                                         eb->diff3_cmd,
                                         eb->cancel_func, eb->cancel_baton,
                                         result_pool, scratch_pool));
    } /* end: working file exists and has mods */
  else
    {
      /* There is no new text base, but let's see if the working file needs
         to be updated for any other reason. */

      apr_hash_t *keywords;

      /* Determine if any of the propchanges are the "magic" ones that
         might require changing the working file. */
      svn_boolean_t magic_props_changed;

      magic_props_changed = svn_wc__has_magic_property(fb->propchanges);

      SVN_ERR(svn_wc__get_translate_info(NULL, NULL,
                                         &keywords,
                                         NULL,
                                         eb->db, fb->local_abspath,
                                         actual_props, TRUE,
                                         scratch_pool, scratch_pool));
      if (magic_props_changed || keywords)
        {
          /* Special edge-case: it's possible that this file installation
             only involves propchanges, but that some of those props still
             require a retranslation of the working file.

             OR that the file doesn't involve propchanges which by themselves
             require retranslation, but receiving a change bumps the revision
             number which requires re-expansion of keywords... */

          if (is_locally_modified)
            {
              const char *tmptext;

              /* Copy and DEtranslate the working file to a temp text-base.
                 Note that detranslation is done according to the old props. */
              SVN_ERR(svn_wc__internal_translated_file(
                        &tmptext, fb->local_abspath, eb->db, fb->local_abspath,
                        SVN_WC_TRANSLATE_TO_NF
                          | SVN_WC_TRANSLATE_NO_OUTPUT_CLEANUP,
                        eb->cancel_func, eb->cancel_baton,
                        result_pool, scratch_pool));

              /* We always want to reinstall the working file if the magic
                 properties have changed, or there are any keywords present.
                 Note that TMPTEXT might actually refer to the working file
                 itself (the above function skips a detranslate when not
                 required). This is acceptable, as we will (re)translate
                 according to the new properties into a temporary file (from
                 the working file), and then rename the temp into place. Magic!
               */
              *install_pristine = TRUE;
              *install_from = tmptext;
            }
          else
            {
              /* Use our existing 'copy' from the pristine store instead
                 of making a new copy. This way we can use the standard code
                 to update the recorded size and modification time.
                 (Issue #3842) */
              *install_pristine = TRUE;
            }
        }
    }

  /* Set the returned content state. */

  if (found_text_conflict)
    *content_state = svn_wc_notify_state_conflicted;
  else if (fb->new_text_base_sha1_checksum)
    {
      if (is_locally_modified)
        *content_state = svn_wc_notify_state_merged;
      else
        *content_state = svn_wc_notify_state_changed;
    }
  else
    *content_state = svn_wc_notify_state_unchanged;

  return SVN_NO_ERROR;
}