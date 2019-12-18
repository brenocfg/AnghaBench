#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_wc__db_install_data_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* close_file ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* apply_textdelta_stream ) (TYPE_1__ const*,void*,char const*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_7__ {void* local_stream; void* base_stream; int /*<<< orphan*/  need_reset; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ open_txdelta_stream_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CORRUPT_TEXT_BASE ; 
 int /*<<< orphan*/  SVN_WC_TRANSLATE_TO_NF ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * copying_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_txdelta_stream ; 
 int /*<<< orphan*/  read_and_checksum_pristine_text (int /*<<< orphan*/ **,int /*<<< orphan*/  const**,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__ const*,void*,char const*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_checksum_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_match (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/ * svn_checksum_mismatch_err (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_to_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_checksum_to_cstring_display (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_checksummed2 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_close (int /*<<< orphan*/ *) ; 
 void* svn_stream_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_install (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_prepare_install (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__internal_translated_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__internal_transmit_text_deltas(svn_stream_t *tempstream,
                                      const svn_checksum_t **new_text_base_md5_checksum,
                                      const svn_checksum_t **new_text_base_sha1_checksum,
                                      svn_wc__db_t *db,
                                      const char *local_abspath,
                                      svn_boolean_t fulltext,
                                      const svn_delta_editor_t *editor,
                                      void *file_baton,
                                      apr_pool_t *result_pool,
                                      apr_pool_t *scratch_pool)
{
  const svn_checksum_t *expected_md5_checksum;  /* recorded MD5 of BASE_S. */
  svn_checksum_t *verify_checksum;  /* calc'd MD5 of BASE_STREAM */
  svn_checksum_t *local_md5_checksum;  /* calc'd MD5 of LOCAL_STREAM */
  svn_checksum_t *local_sha1_checksum;  /* calc'd SHA1 of LOCAL_STREAM */
  svn_wc__db_install_data_t *install_data = NULL;
  svn_error_t *err;
  svn_error_t *err2;
  svn_stream_t *base_stream;  /* delta source */
  svn_stream_t *local_stream;  /* delta target: LOCAL_ABSPATH transl. to NF */

  /* Translated input */
  SVN_ERR(svn_wc__internal_translated_stream(&local_stream, db,
                                             local_abspath, local_abspath,
                                             SVN_WC_TRANSLATE_TO_NF,
                                             scratch_pool, scratch_pool));

  /* If the caller wants a copy of the working file translated to
   * repository-normal form, make the copy by tee-ing the TEMPSTREAM.
   * This is only needed for the 1.6 API.  Even when using the 1.6 API
   * this temporary file is not used by the functions that would have used
   * it when using the 1.6 code.  It's possible that 3rd party users (if
   * there are any) might expect this file to be a text-base. */
  if (tempstream)
    {
      /* Wrap the translated stream with a new stream that writes the
         translated contents into the new text base file as we read from it.
         Note that the new text base file will be closed when the new stream
         is closed. */
      local_stream = copying_stream(local_stream, tempstream, scratch_pool);
    }
  if (new_text_base_sha1_checksum)
    {
      svn_stream_t *new_pristine_stream;

      SVN_ERR(svn_wc__db_pristine_prepare_install(&new_pristine_stream,
                                                  &install_data,
                                                  &local_sha1_checksum, NULL,
                                                  db, local_abspath,
                                                  scratch_pool, scratch_pool));
      local_stream = copying_stream(local_stream, new_pristine_stream,
                                    scratch_pool);
    }

  /* If sending a full text is requested, or if there is no pristine text
   * (e.g. the node is locally added), then set BASE_STREAM to an empty
   * stream and leave EXPECTED_MD5_CHECKSUM and VERIFY_CHECKSUM as NULL.
   *
   * Otherwise, set BASE_STREAM to a stream providing the base (source) text
   * for the delta, set EXPECTED_MD5_CHECKSUM to its stored MD5 checksum,
   * and arrange for its VERIFY_CHECKSUM to be calculated later. */
  if (! fulltext)
    {
      /* We will be computing a delta against the pristine contents */
      /* We need the expected checksum to be an MD-5 checksum rather than a
       * SHA-1 because we want to pass it to apply_textdelta(). */
      SVN_ERR(read_and_checksum_pristine_text(&base_stream,
                                              &expected_md5_checksum,
                                              &verify_checksum,
                                              db, local_abspath,
                                              scratch_pool, scratch_pool));
    }
  else
    {
      /* Send a fulltext. */
      base_stream = svn_stream_empty(scratch_pool);
      expected_md5_checksum = NULL;
      verify_checksum = NULL;
    }

  /* Arrange the stream to calculate the resulting MD5. */
  local_stream = svn_stream_checksummed2(local_stream, &local_md5_checksum,
                                         NULL, svn_checksum_md5, TRUE,
                                         scratch_pool);

  /* Tell the editor to apply a textdelta stream to the file baton. */
  {
    open_txdelta_stream_baton_t baton = { 0 };

    /* apply_textdelta_stream() is working against a base with this checksum */
    const char *base_digest_hex = NULL;

    if (expected_md5_checksum)
      /* ### Why '..._display()'?  expected_md5_checksum should never be all-
       * zero, but if it is, we would want to pass NULL not an all-zero
       * digest to apply_textdelta_stream(), wouldn't we? */
      base_digest_hex = svn_checksum_to_cstring_display(expected_md5_checksum,
                                                        scratch_pool);

    baton.need_reset = FALSE;
    baton.base_stream = svn_stream_disown(base_stream, scratch_pool);
    baton.local_stream = svn_stream_disown(local_stream, scratch_pool);
    err = editor->apply_textdelta_stream(editor, file_baton, base_digest_hex,
                                         open_txdelta_stream, &baton,
                                         scratch_pool);
  }

  /* Close the two streams to force writing the digest */
  err2 = svn_stream_close(base_stream);
  if (err2)
    {
      /* Set verify_checksum to NULL if svn_stream_close() returns error
         because checksum will be uninitialized in this case. */
      verify_checksum = NULL;
      err = svn_error_compose_create(err, err2);
    }

  err = svn_error_compose_create(err, svn_stream_close(local_stream));

  /* If we have an error, it may be caused by a corrupt text base,
     so check the checksum. */
  if (expected_md5_checksum && verify_checksum
      && !svn_checksum_match(expected_md5_checksum, verify_checksum))
    {
      /* The entry checksum does not match the actual text
         base checksum.  Extreme badness. Of course,
         theoretically we could just switch to
         fulltext transmission here, and everything would
         work fine; after all, we're going to replace the
         text base with a new one in a moment anyway, and
         we'd fix the checksum then.  But it's better to
         error out.  People should know that their text
         bases are getting corrupted, so they can
         investigate.  Other commands could be affected,
         too, such as `svn diff'.  */

      err = svn_error_compose_create(
              svn_checksum_mismatch_err(expected_md5_checksum, verify_checksum,
                            scratch_pool,
                            _("Checksum mismatch for text base of '%s'"),
                            svn_dirent_local_style(local_abspath,
                                                   scratch_pool)),
              err);

      return svn_error_create(SVN_ERR_WC_CORRUPT_TEXT_BASE, err, NULL);
    }

  /* Now, handle that delta transmission error if any, so we can stop
     thinking about it after this point. */
  SVN_ERR_W(err, apr_psprintf(scratch_pool,
                              _("While preparing '%s' for commit"),
                              svn_dirent_local_style(local_abspath,
                                                     scratch_pool)));

  if (new_text_base_md5_checksum)
    *new_text_base_md5_checksum = svn_checksum_dup(local_md5_checksum,
                                                   result_pool);
  if (new_text_base_sha1_checksum)
    {
      SVN_ERR(svn_wc__db_pristine_install(install_data,
                                          local_sha1_checksum,
                                          local_md5_checksum,
                                          scratch_pool));
      *new_text_base_sha1_checksum = svn_checksum_dup(local_sha1_checksum,
                                                      result_pool);
    }

  /* Close the file baton, and get outta here. */
  return svn_error_trace(
             editor->close_file(file_baton,
                                svn_checksum_to_cstring(local_md5_checksum,
                                                        scratch_pool),
                                scratch_pool));
}