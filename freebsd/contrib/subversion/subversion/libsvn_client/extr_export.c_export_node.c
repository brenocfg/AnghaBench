#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {scalar_t__ node_status; scalar_t__ kind; char* changed_author; int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  repos_relpath; int /*<<< orphan*/  changed_rev; int /*<<< orphan*/  changed_date; scalar_t__ file_external; } ;
typedef  TYPE_2__ svn_wc_status3_t ;
struct TYPE_28__ {scalar_t__ kind; } ;
typedef  TYPE_3__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_subst_eol_style_t ;
struct TYPE_29__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_30__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_5__ svn_error_t ;
typedef  void* svn_boolean_t ;
struct export_info_baton {char const* origin_abspath; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  ignore_keywords; int /*<<< orphan*/  native_eol; TYPE_1__* revision; int /*<<< orphan*/  overwrite; void* exported; int /*<<< orphan*/  to_path; int /*<<< orphan*/ * wc_ctx; } ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_31__ {int /*<<< orphan*/  protection; } ;
typedef  TYPE_6__ apr_finfo_t ;
typedef  int /*<<< orphan*/  apr_fileperms_t ;
struct TYPE_26__ {scalar_t__ kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FINFO_PROT ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  APR_STATUS_IS_EEXIST (int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/  SVN_ERR_W (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_5__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EOL_STYLE ; 
 int /*<<< orphan*/  SVN_PROP_EXECUTABLE ; 
 int /*<<< orphan*/  SVN_PROP_KEYWORDS ; 
 int /*<<< orphan*/  SVN_PROP_SPECIAL ; 
 void* TRUE ; 
 char* _ (char*) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  get_eol_style (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_5__*) ; 
 TYPE_5__* svn_error_compose_create (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_5__* svn_error_trace (TYPE_5__*) ; 
 TYPE_4__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* svn_io_dir_make (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_affected_time (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_file_rename2 (char const*,char const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (char const*,void*,int /*<<< orphan*/ *) ; 
 TYPE_5__* svn_io_set_file_affected_time (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_5__* svn_io_set_file_executable (char const*,void*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_stat (TYPE_6__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_unknown ; 
 scalar_t__ svn_opt_revision_working ; 
 char* svn_path_url_add_component2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_build_keywords3 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_create_specialfile (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_read_specialfile (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_subst_stream_translated (int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_get_pristine_contents2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_get_pristine_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_update_add ; 
 int /*<<< orphan*/  svn_wc_prop_list2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_status_deleted ; 
 scalar_t__ svn_wc_status_normal ; 

__attribute__((used)) static svn_error_t *
export_node(void *baton,
            const char *local_abspath,
            const svn_wc_status3_t *status,
            apr_pool_t *scratch_pool)
{
  struct export_info_baton *eib = baton;
  svn_wc_context_t *wc_ctx = eib->wc_ctx;
  apr_hash_t *kw = NULL;
  svn_subst_eol_style_t style;
  apr_hash_t *props;
  svn_string_t *eol_style, *keywords, *executable, *special;
  const char *eol = NULL;
  svn_boolean_t local_mod = FALSE;
  apr_time_t tm;
  svn_stream_t *source;
  svn_stream_t *dst_stream;
  const char *dst_tmp;
  svn_error_t *err;

  const char *to_abspath = svn_dirent_join(
                                eib->to_path,
                                svn_dirent_skip_ancestor(eib->origin_abspath,
                                                         local_abspath),
                                scratch_pool);

  eib->exported = TRUE;

  /* Don't export 'deleted' files and directories unless it's a
     revision other than WORKING.  These files and directories
     don't really exist in WORKING. */
  if (eib->revision->kind == svn_opt_revision_working
      && status->node_status == svn_wc_status_deleted)
    return SVN_NO_ERROR;

  if (status->kind == svn_node_dir)
    {
      apr_fileperms_t perm = APR_OS_DEFAULT;

      /* Try to make the new directory.  If this fails because the
         directory already exists, check our FORCE flag to see if we
         care. */

      /* Keep the source directory's permissions if applicable.
         Skip retrieving the umask on windows. Apr does not implement setting
         filesystem privileges on Windows.
         Retrieving the file permissions with APR_FINFO_PROT | APR_FINFO_OWNER
         is documented to be 'incredibly expensive' */
#ifndef WIN32
      if (eib->revision->kind == svn_opt_revision_working)
        {
          apr_finfo_t finfo;
          SVN_ERR(svn_io_stat(&finfo, local_abspath, APR_FINFO_PROT,
                              scratch_pool));
          perm = finfo.protection;
        }
#endif
      err = svn_io_dir_make(to_abspath, perm, scratch_pool);
      if (err)
        {
          if (! APR_STATUS_IS_EEXIST(err->apr_err))
            return svn_error_trace(err);
          if (! eib->overwrite)
            SVN_ERR_W(err, _("Destination directory exists, and will not be "
                             "overwritten unless forced"));
          else
            svn_error_clear(err);
        }

      if (eib->notify_func
          && (strcmp(eib->origin_abspath, local_abspath) != 0))
        {
          svn_wc_notify_t *notify =
              svn_wc_create_notify(to_abspath,
                                   svn_wc_notify_update_add, scratch_pool);

          notify->kind = svn_node_dir;
          (eib->notify_func)(eib->notify_baton, notify, scratch_pool);
        }

      return SVN_NO_ERROR;
    }
  else if (status->kind != svn_node_file)
    {
      if (strcmp(eib->origin_abspath, local_abspath) != 0)
        return SVN_NO_ERROR;

      return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                               _("The node '%s' was not found."),
                               svn_dirent_local_style(local_abspath,
                                                      scratch_pool));
    }

  /* Skip file externals if they are a descendant of the export,
     BUT NOT if we are explictly exporting the file external. */
  if (status->file_external && strcmp(eib->origin_abspath, local_abspath) != 0)
    return SVN_NO_ERROR;

  /* Produce overwrite errors for the export root */
  if (strcmp(local_abspath, eib->origin_abspath) == 0)
    {
      svn_node_kind_t to_kind;

      SVN_ERR(svn_io_check_path(to_abspath, &to_kind, scratch_pool));

      if ((to_kind == svn_node_file || to_kind == svn_node_unknown)
          && !eib->overwrite)
        return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                                 _("Destination file '%s' exists, and "
                                   "will not be overwritten unless forced"),
                                 svn_dirent_local_style(to_abspath,
                                                        scratch_pool));
      else if (to_kind == svn_node_dir)
        return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                                 _("Destination '%s' exists. Cannot "
                                   "overwrite directory with non-directory"),
                                 svn_dirent_local_style(to_abspath,
                                                        scratch_pool));
    }

  if (eib->revision->kind != svn_opt_revision_working)
    {
      /* Only export 'added' files when the revision is WORKING. This is not
         WORKING, so skip the 'added' files, since they didn't exist
         in the BASE revision and don't have an associated text-base.

         'replaced' files are technically the same as 'added' files.
         ### TODO: Handle replaced nodes properly.
         ###       svn_opt_revision_base refers to the "new"
         ###       base of the node. That means, if a node is locally
         ###       replaced, export skips this node, as if it was locally
         ###       added, because svn_opt_revision_base refers to the base
         ###       of the added node, not to the node that was deleted.
         ###       In contrast, when the node is copied-here or moved-here,
         ###       the copy/move source's content will be exported.
         ###       It is currently not possible to export the revert-base
         ###       when a node is locally replaced. We need a new
         ###       svn_opt_revision_ enum value for proper distinction
         ###       between revert-base and commit-base.

         Copied-/moved-here nodes have a base, so export both added and
         replaced files when they involve a copy-/move-here.

         We get all this for free from evaluating SOURCE == NULL:
       */
      SVN_ERR(svn_wc_get_pristine_contents2(&source, wc_ctx, local_abspath,
                                            scratch_pool, scratch_pool));
      if (source == NULL)
        return SVN_NO_ERROR;

      SVN_ERR(svn_wc_get_pristine_props(&props, wc_ctx, local_abspath,
                                        scratch_pool, scratch_pool));
    }
  else
    {
      /* ### hmm. this isn't always a specialfile. this will simply open
         ### the file readonly if it is a regular file. */
      SVN_ERR(svn_subst_read_specialfile(&source, local_abspath, scratch_pool,
                                         scratch_pool));

      SVN_ERR(svn_wc_prop_list2(&props, wc_ctx, local_abspath, scratch_pool,
                                scratch_pool));
      if (status->node_status != svn_wc_status_normal)
        local_mod = TRUE;
    }

  /* We can early-exit if we're creating a special file. */
  special = svn_hash_gets(props, SVN_PROP_SPECIAL);
  if (special != NULL)
    {
      /* Create the destination as a special file, and copy the source
         details into the destination stream. */
      /* ### And forget the notification */
      SVN_ERR(svn_subst_create_specialfile(&dst_stream, to_abspath,
                                           scratch_pool, scratch_pool));
      return svn_error_trace(
        svn_stream_copy3(source, dst_stream, NULL, NULL, scratch_pool));
    }


  eol_style = svn_hash_gets(props, SVN_PROP_EOL_STYLE);
  keywords = svn_hash_gets(props, SVN_PROP_KEYWORDS);
  executable = svn_hash_gets(props, SVN_PROP_EXECUTABLE);

  if (eol_style)
    SVN_ERR(get_eol_style(&style, &eol, eol_style->data, eib->native_eol));

  if (local_mod)
    {
      /* Use the modified time from the working copy of
         the file */
      SVN_ERR(svn_io_file_affected_time(&tm, local_abspath, scratch_pool));
    }
  else
    {
      tm = status->changed_date;
    }

  if (keywords)
    {
      svn_revnum_t changed_rev = status->changed_rev;
      const char *suffix;
      const char *url = svn_path_url_add_component2(status->repos_root_url,
                                                    status->repos_relpath,
                                                    scratch_pool);
      const char *author = status->changed_author;
      if (local_mod)
        {
          /* For locally modified files, we'll append an 'M'
             to the revision number, and set the author to
             "(local)" since we can't always determine the
             current user's username */
          suffix = "M";
          author = _("(local)");
        }
      else
        {
          suffix = "";
        }

      SVN_ERR(svn_subst_build_keywords3(&kw, keywords->data,
                                        apr_psprintf(scratch_pool, "%ld%s",
                                                     changed_rev, suffix),
                                        url, status->repos_root_url, tm,
                                        author, scratch_pool));
    }

  /* For atomicity, we translate to a tmp file and then rename the tmp file
     over the real destination. */
  SVN_ERR(svn_stream_open_unique(&dst_stream, &dst_tmp,
                                 svn_dirent_dirname(to_abspath, scratch_pool),
                                 svn_io_file_del_none, scratch_pool,
                                 scratch_pool));

  /* If some translation is needed, then wrap the output stream (this is
     more efficient than wrapping the input). */
  if (eol || (kw && (apr_hash_count(kw) > 0)))
    dst_stream = svn_subst_stream_translated(dst_stream,
                                             eol,
                                             FALSE /* repair */,
                                             kw,
                                             ! eib->ignore_keywords /* expand */,
                                             scratch_pool);

  /* ###: use cancel func/baton in place of NULL/NULL below. */
  err = svn_stream_copy3(source, dst_stream, NULL, NULL, scratch_pool);

  if (!err && executable)
    err = svn_io_set_file_executable(dst_tmp, TRUE, FALSE, scratch_pool);

  if (!err)
    err = svn_io_set_file_affected_time(tm, dst_tmp, scratch_pool);

  if (err)
    return svn_error_compose_create(err, svn_io_remove_file2(dst_tmp, FALSE,
                                                             scratch_pool));

  /* Now that dst_tmp contains the translated data, do the atomic rename. */
  SVN_ERR(svn_io_file_rename2(dst_tmp, to_abspath, FALSE, scratch_pool));

  if (eib->notify_func)
    {
      svn_wc_notify_t *notify = svn_wc_create_notify(to_abspath,
                                      svn_wc_notify_update_add, scratch_pool);
      notify->kind = svn_node_file;
      (eib->notify_func)(eib->notify_baton, notify, scratch_pool);
    }

  return SVN_NO_ERROR;
}