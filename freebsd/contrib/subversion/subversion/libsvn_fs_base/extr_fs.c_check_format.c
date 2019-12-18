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
 int SVN_FS_BASE__FORMAT_NUMBER ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static svn_error_t *
check_format(int format)
{
  /* We currently support any format less than the compiled format number
     simultaneously.  */
  if (format <= SVN_FS_BASE__FORMAT_NUMBER)
    return SVN_NO_ERROR;

  return svn_error_createf(
        SVN_ERR_FS_UNSUPPORTED_FORMAT, NULL,
        _("Expected FS format '%d'; found format '%d'"),
        SVN_FS_BASE__FORMAT_NUMBER, format);
}