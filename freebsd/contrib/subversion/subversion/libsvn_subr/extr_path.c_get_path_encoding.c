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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int APR_FILEPATH_ENCODING_UTF8 ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_filepath_encoding (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_path_encoding(svn_boolean_t *path_is_utf8, apr_pool_t *pool)
{
  apr_status_t apr_err;
  int encoding_style;

  apr_err = apr_filepath_encoding(&encoding_style, pool);
  if (apr_err)
    return svn_error_wrap_apr(apr_err,
                              _("Can't determine the native path encoding"));

  /* ### What to do about APR_FILEPATH_ENCODING_UNKNOWN?
     Well, for now we'll just punt to the svn_utf_ functions;
     those will at least do the ASCII-subset check. */
  *path_is_utf8 = (encoding_style == APR_FILEPATH_ENCODING_UTF8);
  return SVN_NO_ERROR;
}