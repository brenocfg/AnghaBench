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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_7__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; } ;
typedef  TYPE_2__ pair_cache_key_t ;
struct TYPE_9__ {int /*<<< orphan*/  revprop_cache; int /*<<< orphan*/  revprop_prefix; } ;
typedef  TYPE_3__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_cache__has_key (scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
cache_revprops(svn_boolean_t *is_cached,
               svn_fs_t *fs,
               svn_revnum_t revision,
               svn_string_t *content,
               apr_pool_t *scratch_pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  pair_cache_key_t key;

  /* Make sure prepare_revprop_cache() has been called. */
  SVN_ERR_ASSERT(ffd->revprop_prefix);
  key.revision = revision;
  key.second = ffd->revprop_prefix;

  if (is_cached)
    {
      SVN_ERR(svn_cache__has_key(is_cached, ffd->revprop_cache, &key,
                                 scratch_pool));
      if (*is_cached)
        return SVN_NO_ERROR;
    }

  SVN_ERR(svn_cache__set(ffd->revprop_cache, &key, content, scratch_pool));

  return SVN_NO_ERROR;
}