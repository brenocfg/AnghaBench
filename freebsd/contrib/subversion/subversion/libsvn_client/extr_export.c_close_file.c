#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_3__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_subst_eol_style_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct file_baton {struct edit_baton* edit_baton; int /*<<< orphan*/  path; scalar_t__ date; int /*<<< orphan*/  special; scalar_t__ executable_val; int /*<<< orphan*/  tmppath; int /*<<< orphan*/  author; int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  url; int /*<<< orphan*/  revision; TYPE_2__* keywords_val; TYPE_1__* eol_style_val; int /*<<< orphan*/  text_digest; int /*<<< orphan*/  tmp_stream; } ;
struct edit_baton {int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  native_eol; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_eol_style (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_checksum__from_digest_md5 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/ * svn_checksum_mismatch_err (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_rename2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_set_file_affected_time (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_set_file_executable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_subst_build_keywords3 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_copy_and_translate4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc_create_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_update_add ; 

__attribute__((used)) static svn_error_t *
close_file(void *file_baton,
           const char *text_digest,
           apr_pool_t *pool)
{
  struct file_baton *fb = file_baton;
  struct edit_baton *eb = fb->edit_baton;
  svn_checksum_t *text_checksum;
  svn_checksum_t *actual_checksum;

  /* Was a txdelta even sent? */
  if (! fb->tmppath)
    return SVN_NO_ERROR;

  SVN_ERR(svn_stream_close(fb->tmp_stream));

  SVN_ERR(svn_checksum_parse_hex(&text_checksum, svn_checksum_md5, text_digest,
                                 pool));
  actual_checksum = svn_checksum__from_digest_md5(fb->text_digest, pool);

  /* Note that text_digest can be NULL when talking to certain repositories.
     In that case text_checksum will be NULL and the following match code
     will note that the checksums match */
  if (!svn_checksum_match(text_checksum, actual_checksum))
    return svn_checksum_mismatch_err(text_checksum, actual_checksum, pool,
                                     _("Checksum mismatch for '%s'"),
                                     svn_dirent_local_style(fb->path, pool));

  if ((! fb->eol_style_val) && (! fb->keywords_val) && (! fb->special))
    {
      SVN_ERR(svn_io_file_rename2(fb->tmppath, fb->path, FALSE, pool));
    }
  else
    {
      svn_subst_eol_style_t style;
      const char *eol = NULL;
      svn_boolean_t repair = FALSE;
      apr_hash_t *final_kw = NULL;

      if (fb->eol_style_val)
        {
          SVN_ERR(get_eol_style(&style, &eol, fb->eol_style_val->data,
                                eb->native_eol));
          repair = TRUE;
        }

      if (fb->keywords_val)
        SVN_ERR(svn_subst_build_keywords3(&final_kw, fb->keywords_val->data,
                                          fb->revision, fb->url,
                                          fb->repos_root_url, fb->date,
                                          fb->author, pool));

      SVN_ERR(svn_subst_copy_and_translate4(fb->tmppath, fb->path,
                                            eol, repair, final_kw,
                                            TRUE, /* expand */
                                            fb->special,
                                            eb->cancel_func, eb->cancel_baton,
                                            pool));

      SVN_ERR(svn_io_remove_file2(fb->tmppath, FALSE, pool));
    }

  if (fb->executable_val)
    SVN_ERR(svn_io_set_file_executable(fb->path, TRUE, FALSE, pool));

  if (fb->date && (! fb->special))
    SVN_ERR(svn_io_set_file_affected_time(fb->date, fb->path, pool));

  if (fb->edit_baton->notify_func)
    {
      svn_wc_notify_t *notify = svn_wc_create_notify(fb->path,
                                                     svn_wc_notify_update_add,
                                                     pool);
      notify->kind = svn_node_file;
      (*fb->edit_baton->notify_func)(fb->edit_baton->notify_baton, notify,
                                     pool);
    }

  return SVN_NO_ERROR;
}