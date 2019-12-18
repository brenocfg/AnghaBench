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
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* tag; scalar_t__ patch; } ;
typedef  TYPE_1__ svn_version_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_9__ {int major; int minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_COMPATIBLE_VERSION ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_PRE_1_4_COMPATIBLE ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_PRE_1_5_COMPATIBLE ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_PRE_1_6_COMPATIBLE ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_PRE_1_8_COMPATIBLE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  add_compatility (TYPE_1__*,int,int) ; 
 TYPE_1__* apr_pmemdup (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_subr_version () ; 
 int /*<<< orphan*/  svn_version__parse_version_string (TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs__compatible_version(svn_version_t **compatible_version,
                           apr_hash_t *config,
                           apr_pool_t *pool)
{
  svn_version_t *version;
  const char *compatible;

  /* set compatible version according to generic option.
     Make sure, we are always compatible to the current SVN version
     (or older). */
  compatible = svn_hash_gets(config, SVN_FS_CONFIG_COMPATIBLE_VERSION);
  if (compatible)
    {
      SVN_ERR(svn_version__parse_version_string(&version,
                                                compatible, pool));
      add_compatility(version,
                      svn_subr_version()->major,
                      svn_subr_version()->minor);
    }
  else
    {
      version = apr_pmemdup(pool, svn_subr_version(), sizeof(*version));
    }

  /* specific options take precedence.
     Let the lowest version compatibility requirement win */
  if (svn_hash_gets(config, SVN_FS_CONFIG_PRE_1_4_COMPATIBLE))
    add_compatility(version, 1, 3);
  else if (svn_hash_gets(config, SVN_FS_CONFIG_PRE_1_5_COMPATIBLE))
    add_compatility(version, 1, 4);
  else if (svn_hash_gets(config, SVN_FS_CONFIG_PRE_1_6_COMPATIBLE))
    add_compatility(version, 1, 5);
  else if (svn_hash_gets(config, SVN_FS_CONFIG_PRE_1_8_COMPATIBLE))
    add_compatility(version, 1, 7);

  /* we ignored the patch level and tag so far.
   * Give them a defined value. */
  version->patch = 0;
  version->tag = "";

  /* done here */
  *compatible_version = version;
  return SVN_NO_ERROR;
}