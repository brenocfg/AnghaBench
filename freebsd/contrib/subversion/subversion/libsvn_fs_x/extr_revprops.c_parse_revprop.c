#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_8__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ svn_fs_x__pair_cache_key_t ;
struct TYPE_9__ {int /*<<< orphan*/  revprop_cache; int /*<<< orphan*/  revprop_generation; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_10__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ has_revprop_cache (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_generation_valid (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_cache__set (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__parse_properties (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
parse_revprop(apr_hash_t **properties,
              svn_fs_t *fs,
              svn_revnum_t revision,
              const svn_string_t *content,
              apr_pool_t *result_pool,
              apr_pool_t *scratch_pool)
{
  SVN_ERR_W(svn_fs_x__parse_properties(properties, content, result_pool),
            apr_psprintf(scratch_pool, "Failed to parse revprops for r%ld.",
                         revision));

  if (has_revprop_cache(fs, scratch_pool))
    {
      svn_fs_x__data_t *ffd = fs->fsap_data;
      svn_fs_x__pair_cache_key_t key = { 0 };

      SVN_ERR_ASSERT(is_generation_valid(fs));

      key.revision = revision;
      key.second = ffd->revprop_generation;
      SVN_ERR(svn_cache__set(ffd->revprop_cache, &key, *properties,
                             scratch_pool));
    }

  return SVN_NO_ERROR;
}