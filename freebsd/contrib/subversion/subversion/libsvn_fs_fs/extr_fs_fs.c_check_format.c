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
 int SVN_FS_FS__FORMAT_NUMBER ; 
 int SVN_FS_FS__PACKED_REVPROP_SQLITE_DEV_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static svn_error_t *
check_format(int format)
{
  /* Blacklist.  These formats may be either younger or older than
     SVN_FS_FS__FORMAT_NUMBER, but we don't support them. */
  if (format == SVN_FS_FS__PACKED_REVPROP_SQLITE_DEV_FORMAT)
    return svn_error_createf(SVN_ERR_FS_UNSUPPORTED_FORMAT, NULL,
                             _("Found format '%d', only created by "
                               "unreleased dev builds; see "
                               "http://subversion.apache.org"
                               "/docs/release-notes/1.7#revprop-packing"),
                             format);

  /* We support all formats from 1-current simultaneously */
  if (1 <= format && format <= SVN_FS_FS__FORMAT_NUMBER)
    return SVN_NO_ERROR;

  return svn_error_createf(SVN_ERR_FS_UNSUPPORTED_FORMAT, NULL,
     _("Expected FS format between '1' and '%d'; found format '%d'"),
     SVN_FS_FS__FORMAT_NUMBER, format);
}