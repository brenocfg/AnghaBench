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

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_UNSUPPORTED_FORMAT ; 
 int SVN_FS_X__EXPERIMENTAL_FORMAT_NUMBER ; 
 int SVN_FS_X__FORMAT_NUMBER ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,...) ; 

__attribute__((used)) static svn_error_t *
check_format(int format)
{
  /* Put blacklisted versions here. */

  /* We support any format if it matches the current format. */
  if (format == SVN_FS_X__FORMAT_NUMBER)
    return SVN_NO_ERROR;

  /* Experimental formats are only supported if they match the current, but
   * that case has already been handled. So, reject any experimental format.
   */
  if (SVN_FS_X__EXPERIMENTAL_FORMAT_NUMBER >= format)
    return svn_error_createf(SVN_ERR_FS_UNSUPPORTED_FORMAT, NULL,
      _("Unsupported experimental FSX format '%d' found; current format is '%d'"),
      format, SVN_FS_X__FORMAT_NUMBER);

  /* By default, we will support any non-experimental format released so far.
   */
  if (format <= SVN_FS_X__FORMAT_NUMBER)
    return SVN_NO_ERROR;

  return svn_error_createf(SVN_ERR_FS_UNSUPPORTED_FORMAT, NULL,
     _("Expected FSX format between '%d' and '%d'; found format '%d'"),
     SVN_FS_X__EXPERIMENTAL_FORMAT_NUMBER + 1, SVN_FS_X__FORMAT_NUMBER,
     format);
}