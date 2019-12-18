#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
struct TYPE_10__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_IO_INCONSISTENT_EOL ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_special_file_from_stream (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  detranslate_special_file (char const*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_error_compose_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_createf (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_special_path (char const*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_file (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_perms (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_read_specialfile (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_subst_stream_translated (int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_subst_copy_and_translate4(const char *src,
                              const char *dst,
                              const char *eol_str,
                              svn_boolean_t repair,
                              apr_hash_t *keywords,
                              svn_boolean_t expand,
                              svn_boolean_t special,
                              svn_cancel_func_t cancel_func,
                              void *cancel_baton,
                              apr_pool_t *pool)
{
  svn_stream_t *src_stream;
  svn_stream_t *dst_stream;
  const char *dst_tmp;
  svn_error_t *err;
  svn_node_kind_t kind;
  svn_boolean_t path_special;

  SVN_ERR(svn_io_check_special_path(src, &kind, &path_special, pool));

  /* If this is a 'special' file, we may need to create it or
     detranslate it. */
  if (special || path_special)
    {
      if (expand)
        {
          if (path_special)
            {
              /* We are being asked to create a special file from a special
                 file.  Do a temporary detranslation and work from there. */

              /* ### woah. this section just undoes all the work we already did
                 ### to read the contents of the special file. shoot... the
                 ### svn_subst_read_specialfile even checks the file type
                 ### for us! */

              SVN_ERR(svn_subst_read_specialfile(&src_stream, src, pool, pool));
            }
          else
            {
              SVN_ERR(svn_stream_open_readonly(&src_stream, src, pool, pool));
            }

          SVN_ERR(create_special_file_from_stream(src_stream, dst, pool));

          return svn_error_trace(svn_stream_close(src_stream));
        }
      /* else !expand */

      return svn_error_trace(detranslate_special_file(src, dst,
                                                      cancel_func,
                                                      cancel_baton,
                                                      pool));
    }

  /* The easy way out:  no translation needed, just copy. */
  if (! (eol_str || (keywords && (apr_hash_count(keywords) > 0))))
    return svn_error_trace(svn_io_copy_file(src, dst, FALSE, pool));

  /* Open source file. */
  SVN_ERR(svn_stream_open_readonly(&src_stream, src, pool, pool));

  /* For atomicity, we translate to a tmp file and then rename the tmp file
     over the real destination. */
  SVN_ERR(svn_stream_open_unique(&dst_stream, &dst_tmp,
                                 svn_dirent_dirname(dst, pool),
                                 svn_io_file_del_none, pool, pool));

  dst_stream = svn_subst_stream_translated(dst_stream, eol_str, repair,
                                           keywords, expand, pool);

  /* ###: use cancel func/baton in place of NULL/NULL below. */
  err = svn_stream_copy3(src_stream, dst_stream, cancel_func, cancel_baton,
                         pool);
  if (err)
    {
      /* On errors, we have a pathname available. */
      if (err->apr_err == SVN_ERR_IO_INCONSISTENT_EOL)
        err = svn_error_createf(SVN_ERR_IO_INCONSISTENT_EOL, err,
                                _("File '%s' has inconsistent newlines"),
                                svn_dirent_local_style(src, pool));
      return svn_error_compose_create(err, svn_io_remove_file2(dst_tmp,
                                                               FALSE, pool));
    }

  /* Now that dst_tmp contains the translated data, do the atomic rename. */
  SVN_ERR(svn_io_file_rename2(dst_tmp, dst, FALSE, pool));

  /* Preserve the source file's permission bits. */
  SVN_ERR(svn_io_copy_perms(src, dst, pool));

  return SVN_NO_ERROR;
}