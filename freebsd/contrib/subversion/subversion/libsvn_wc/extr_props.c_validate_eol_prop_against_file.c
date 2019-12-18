#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* (* svn_wc_canonicalize_svn_prop_get_file_t ) (TYPE_2__ const**,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ;
struct TYPE_16__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_15__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 scalar_t__ SVN_ERR_IO_INCONSISTENT_EOL ; 
 int /*<<< orphan*/  SVN_PROP_EOL_STYLE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char const* svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_error_compose_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,char const*,...) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 scalar_t__ svn_mime_type_is_binary (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_subst_stream_translated (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
validate_eol_prop_against_file(const char *path,
                               svn_wc_canonicalize_svn_prop_get_file_t getter,
                               void *getter_baton,
                               apr_pool_t *pool)
{
  svn_stream_t *translating_stream;
  svn_error_t *err;
  const svn_string_t *mime_type;
  const char *path_display
    = svn_path_is_url(path) ? path : svn_dirent_local_style(path, pool);

  /* First just ask the "getter" for the MIME type. */
  SVN_ERR(getter(&mime_type, NULL, getter_baton, pool));

  /* See if this file has been determined to be binary. */
  if (mime_type && svn_mime_type_is_binary(mime_type->data))
    return svn_error_createf
      (SVN_ERR_ILLEGAL_TARGET, NULL,
       _("Can't set '%s': "
         "file '%s' has binary mime type property"),
       SVN_PROP_EOL_STYLE, path_display);

  /* Now ask the getter for the contents of the file; this will do a
     newline translation.  All we really care about here is whether or
     not the function fails on inconsistent line endings.  The
     function is "translating" to an empty stream.  This is
     sneeeeeeeeeeeaky. */
  translating_stream = svn_subst_stream_translated(svn_stream_empty(pool),
                                                   "", FALSE, NULL, FALSE,
                                                   pool);

  err = getter(NULL, translating_stream, getter_baton, pool);

  err = svn_error_compose_create(err, svn_stream_close(translating_stream));

  if (err && err->apr_err == SVN_ERR_IO_INCONSISTENT_EOL)
    return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, err,
                             _("File '%s' has inconsistent newlines"),
                             path_display);

  return svn_error_trace(err);
}