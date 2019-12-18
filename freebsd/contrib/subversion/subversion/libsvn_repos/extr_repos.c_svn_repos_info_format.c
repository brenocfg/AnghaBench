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
struct TYPE_6__ {int minor; char* tag; scalar_t__ patch; int /*<<< orphan*/  major; } ;
typedef  TYPE_1__ svn_version_t ;
struct TYPE_7__ {int format; } ;
typedef  TYPE_2__ svn_repos_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
#define  SVN_REPOS__FORMAT_NUMBER_1_4 129 
#define  SVN_REPOS__FORMAT_NUMBER_LEGACY 128 
 int /*<<< orphan*/  SVN_VER_MAJOR ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 

svn_error_t *
svn_repos_info_format(int *repos_format,
                      svn_version_t **supports_version,
                      svn_repos_t *repos,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  *repos_format = repos->format;
  *supports_version = apr_palloc(result_pool, sizeof(svn_version_t));

  (*supports_version)->major = SVN_VER_MAJOR;
  (*supports_version)->minor = 0;
  (*supports_version)->patch = 0;
  (*supports_version)->tag = "";

  switch (repos->format)
    {
    case SVN_REPOS__FORMAT_NUMBER_LEGACY:
      break;
    case SVN_REPOS__FORMAT_NUMBER_1_4:
      (*supports_version)->minor = 4;
      break;
#ifdef SVN_DEBUG
# if SVN_REPOS__FORMAT_NUMBER != SVN_REPOS__FORMAT_NUMBER_1_4
#  error "Need to add a 'case' statement here"
# endif
#endif
    }

  return SVN_NO_ERROR;
}