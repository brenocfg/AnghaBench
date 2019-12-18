#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int minor; char* tag; scalar_t__ patch; int /*<<< orphan*/  major; } ;
typedef  TYPE_1__ svn_version_t ;
struct TYPE_8__ {int format; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_9__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VER_MAJOR ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 

svn_error_t *
svn_fs_x__info_format(int *fs_format,
                      svn_version_t **supports_version,
                      svn_fs_t *fs,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  *fs_format = ffd->format;
  *supports_version = apr_palloc(result_pool, sizeof(svn_version_t));

  (*supports_version)->major = SVN_VER_MAJOR;
  (*supports_version)->minor = 9;
  (*supports_version)->patch = 0;
  (*supports_version)->tag = "";

  switch (ffd->format)
    {
    case 1:
      break;
    case 2:
      (*supports_version)->minor = 10;
      break;
#ifdef SVN_DEBUG
# if SVN_FS_X__FORMAT_NUMBER != 2
#  error "Need to add a 'case' statement here"
# endif
#endif
    }

  return SVN_NO_ERROR;
}