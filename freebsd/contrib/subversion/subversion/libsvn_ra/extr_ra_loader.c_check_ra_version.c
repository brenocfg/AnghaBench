#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  patch; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
typedef  TYPE_1__ svn_version_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_VERSION_MISMATCH ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_ra_version () ; 
 int /*<<< orphan*/  svn_ver_equal (TYPE_1__ const*,TYPE_1__ const*) ; 

__attribute__((used)) static svn_error_t *
check_ra_version(const svn_version_t *ra_version, const char *scheme)
{
  const svn_version_t *my_version = svn_ra_version();
  if (!svn_ver_equal(my_version, ra_version))
    return svn_error_createf(SVN_ERR_VERSION_MISMATCH, NULL,
                             _("Mismatched RA version for '%s':"
                               " found %d.%d.%d%s,"
                               " expected %d.%d.%d%s"),
                             scheme,
                             my_version->major, my_version->minor,
                             my_version->patch, my_version->tag,
                             ra_version->major, ra_version->minor,
                             ra_version->patch, ra_version->tag);

  return SVN_NO_ERROR;
}