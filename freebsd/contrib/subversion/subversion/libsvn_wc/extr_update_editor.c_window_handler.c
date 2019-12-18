#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct handler_baton {int /*<<< orphan*/  pool; scalar_t__ install_data; int /*<<< orphan*/  new_text_base_sha1_checksum; int /*<<< orphan*/  new_text_base_md5_digest; TYPE_1__* actual_source_checksum; TYPE_1__* expected_source_checksum; int /*<<< orphan*/  source_checksum_stream; int /*<<< orphan*/  apply_baton; int /*<<< orphan*/ * (* apply_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;struct file_baton* fb; } ;
struct file_baton {int /*<<< orphan*/  new_text_base_md5_checksum; int /*<<< orphan*/  new_text_base_sha1_checksum; int /*<<< orphan*/  pool; int /*<<< orphan*/  local_abspath; } ;
struct TYPE_4__ {scalar_t__ kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CORRUPT_TEXT_BASE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum__from_digest_md5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_match (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_checksum_to_cstring (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_install (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_install_abort (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
window_handler(svn_txdelta_window_t *window, void *baton)
{
  struct handler_baton *hb = baton;
  struct file_baton *fb = hb->fb;
  svn_error_t *err;

  /* Apply this window.  We may be done at that point.  */
  err = hb->apply_handler(window, hb->apply_baton);
  if (window != NULL && !err)
    return SVN_NO_ERROR;

  if (hb->expected_source_checksum)
    {
      /* Close the stream to calculate HB->actual_source_md5_checksum. */
      svn_error_t *err2 = svn_stream_close(hb->source_checksum_stream);

      if (!err2)
        {
          SVN_ERR_ASSERT(hb->expected_source_checksum->kind ==
                        hb->actual_source_checksum->kind);

          if (!svn_checksum_match(hb->expected_source_checksum,
                                  hb->actual_source_checksum))
            {
              err = svn_error_createf(SVN_ERR_WC_CORRUPT_TEXT_BASE, err,
                        _("Checksum mismatch while updating '%s':\n"
                          "   expected:  %s\n"
                          "     actual:  %s\n"),
                        svn_dirent_local_style(fb->local_abspath, hb->pool),
                        svn_checksum_to_cstring(hb->expected_source_checksum,
                                                hb->pool),
                        svn_checksum_to_cstring(hb->actual_source_checksum,
                                                hb->pool));
            }
        }

      err = svn_error_compose_create(err, err2);
    }

  if (err)
    {
      /* We failed to apply the delta; clean up the temporary file if it
         already created by lazy_open_target(). */
      if (hb->install_data)
        {
          svn_error_clear(svn_wc__db_pristine_install_abort(hb->install_data,
                                                            hb->pool));
        }
    }
  else
    {
      /* Tell the file baton about the new text base's checksums. */
      fb->new_text_base_md5_checksum =
        svn_checksum__from_digest_md5(hb->new_text_base_md5_digest, fb->pool);
      fb->new_text_base_sha1_checksum =
        svn_checksum_dup(hb->new_text_base_sha1_checksum, fb->pool);

      /* Store the new pristine text in the pristine store now.  Later, in a
         single transaction we will update the BASE_NODE to include a
         reference to this pristine text's checksum. */
      SVN_ERR(svn_wc__db_pristine_install(hb->install_data,
                                          fb->new_text_base_sha1_checksum,
                                          fb->new_text_base_md5_checksum,
                                          hb->pool));
    }

  svn_pool_destroy(hb->pool);

  return err;
}