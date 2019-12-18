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
struct TYPE_6__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_subst_eol_style_t ;
struct TYPE_7__ {char* data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  scalar_t__ svn_boolean_t ;
struct edit_baton {int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  native_eol; int /*<<< orphan*/  ignore_keywords; int /*<<< orphan*/  root_url; int /*<<< orphan*/  root_path; } ;
typedef  scalar_t__ apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_COMMITTED_DATE ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_COMMITTED_REV ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_LAST_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_EOL_STYLE ; 
 int /*<<< orphan*/  SVN_PROP_EXECUTABLE ; 
 int /*<<< orphan*/  SVN_PROP_KEYWORDS ; 
 int /*<<< orphan*/  SVN_PROP_SPECIAL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  get_eol_style (int /*<<< orphan*/ *,char const**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_file_rename2 (char const*,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_set_file_affected_time (scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_set_file_executable (char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_file ; 
 char* svn_path_url_add_component2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_build_keywords3 (int /*<<< orphan*/ **,char*,char const*,char const*,int /*<<< orphan*/ ,scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_create_specialfile (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_subst_stream_translated (int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_time_from_cstring (scalar_t__*,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_update_add ; 

__attribute__((used)) static svn_error_t *
add_file_ev2(void *baton,
             const char *relpath,
             const svn_checksum_t *checksum,
             svn_stream_t *contents,
             apr_hash_t *props,
             svn_revnum_t replaces_rev,
             apr_pool_t *scratch_pool)
{
  struct edit_baton *eb = baton;
  const char *full_path = svn_dirent_join(eb->root_path, relpath,
                                          scratch_pool);
  /* RELPATH is not canonicalized, i.e. it may still contain spaces etc.
   * but EB->root_url is. */
  const char *full_url = svn_path_url_add_component2(eb->root_url,
                                                     relpath,
                                                     scratch_pool);
  const svn_string_t *val;
  /* The four svn: properties we might actually care about. */
  const svn_string_t *eol_style_val = NULL;
  const svn_string_t *keywords_val = NULL;
  const svn_string_t *executable_val = NULL;
  svn_boolean_t special = FALSE;
  /* Any keyword vals to be substituted */
  const char *revision = NULL;
  const char *author = NULL;
  apr_time_t date = 0;

  /* Look at any properties for additional information. */
  if ( (val = svn_hash_gets(props, SVN_PROP_EOL_STYLE)) )
    eol_style_val = val;

  if ( !eb->ignore_keywords && (val = svn_hash_gets(props, SVN_PROP_KEYWORDS)) )
    keywords_val = val;

  if ( (val = svn_hash_gets(props, SVN_PROP_EXECUTABLE)) )
    executable_val = val;

  /* Try to fill out the baton's keywords-structure too. */
  if ( (val = svn_hash_gets(props, SVN_PROP_ENTRY_COMMITTED_REV)) )
    revision = val->data;

  if ( (val = svn_hash_gets(props, SVN_PROP_ENTRY_COMMITTED_DATE)) )
    SVN_ERR(svn_time_from_cstring(&date, val->data, scratch_pool));

  if ( (val = svn_hash_gets(props, SVN_PROP_ENTRY_LAST_AUTHOR)) )
    author = val->data;

  if ( (val = svn_hash_gets(props, SVN_PROP_SPECIAL)) )
    special = TRUE;

  if (special)
    {
      svn_stream_t *tmp_stream;

      SVN_ERR(svn_subst_create_specialfile(&tmp_stream, full_path,
                                           scratch_pool, scratch_pool));
      SVN_ERR(svn_stream_copy3(contents, tmp_stream, eb->cancel_func,
                               eb->cancel_baton, scratch_pool));
    }
  else
    {
      svn_stream_t *tmp_stream;
      const char *tmppath;

      /* Create a temporary file in the same directory as the file. We're going
         to rename the thing into place when we're done. */
      SVN_ERR(svn_stream_open_unique(&tmp_stream, &tmppath,
                                     svn_dirent_dirname(full_path,
                                                        scratch_pool),
                                     svn_io_file_del_none,
                                     scratch_pool, scratch_pool));

      /* Possibly wrap the stream to be translated, as dictated by
         the props. */
      if (eol_style_val || keywords_val)
        {
          svn_subst_eol_style_t style;
          const char *eol = NULL;
          svn_boolean_t repair = FALSE;
          apr_hash_t *final_kw = NULL;

          if (eol_style_val)
            {
              SVN_ERR(get_eol_style(&style, &eol, eol_style_val->data,
                                    eb->native_eol));
              repair = TRUE;
            }

          if (keywords_val)
            SVN_ERR(svn_subst_build_keywords3(&final_kw, keywords_val->data,
                                              revision, full_url,
                                              eb->repos_root_url,
                                              date, author, scratch_pool));

          /* Writing through a translated stream is more efficient than
             reading through one, so we wrap TMP_STREAM and not CONTENTS. */
          tmp_stream = svn_subst_stream_translated(tmp_stream, eol, repair,
                                                   final_kw, TRUE, /* expand */
                                                   scratch_pool);
        }

      SVN_ERR(svn_stream_copy3(contents, tmp_stream, eb->cancel_func,
                               eb->cancel_baton, scratch_pool));

      /* Move the file into place. */
      SVN_ERR(svn_io_file_rename2(tmppath, full_path, FALSE, scratch_pool));
    }

  if (executable_val)
    SVN_ERR(svn_io_set_file_executable(full_path, TRUE, FALSE, scratch_pool));

  if (date && (! special))
    SVN_ERR(svn_io_set_file_affected_time(date, full_path, scratch_pool));

  if (eb->notify_func)
    {
      svn_wc_notify_t *notify = svn_wc_create_notify(full_path,
                                                     svn_wc_notify_update_add,
                                                     scratch_pool);
      notify->kind = svn_node_file;
      (*eb->notify_func)(eb->notify_baton, notify, scratch_pool);
    }

  return SVN_NO_ERROR;
}